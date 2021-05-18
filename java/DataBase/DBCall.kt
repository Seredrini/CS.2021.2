package com.example.myapplication.DataBase

import android.content.Context
import android.os.Build
import android.util.Log
import androidx.annotation.RequiresApi
import com.example.myapplication.Entity.*
import java.util.*
import java.util.concurrent.Callable
import java.util.concurrent.Executors
import java.util.concurrent.FutureTask
import kotlin.collections.ArrayList

class DBCall (context: Context) {

    private val context: Context = context
    private var db: AppDatabase? = null

    public fun add() {
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val ex = Exercise(null, 1, 1)
            val d = ExDate(null, 1, 4, 2020)
            db?.ExDateDao()?.insert(d)
            db?.ExerciseDao()?.insert(ex)
        }
        t.start()
        t.join()
    }

    // удаление тренировки из списка
    public fun deleteTraining(tr: Training?) : List<Training>? {
        var list : List<Training>? = null
        val t = Thread{
                    db = AppDatabase.getDatabase(context);
                    if (tr != null) {
                        db?.TrainingDao()?.delete(tr)
                        list = db?.TrainingDao()?.getAll()
                    }
        }
        t.start()
        t.join()
        return list
    }


    // получение списка мышц
    public fun getMuscle() : List<Muscle>? {
        var list : List<Muscle>? = null
        val r = Callable<List<Muscle>> {
            db = AppDatabase.getDatabase(context);
            list =  db?.MuscleDao()?.getAll()
            return@Callable list
        }
        val task = FutureTask<List<Muscle>>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone){}
        return list
    }


    //получение списка id по списку упражнений
    public fun getIdsExList(list: List<ExerciseList>) : ArrayList<Int>? {
        var ids = ArrayList<Int>()
        val r = Callable<ArrayList<Int>> {
            db = AppDatabase.getDatabase(context);
            for (ex in list){
                ex.ID_ExList?.let { ids.add(it) }
            }
            return@Callable ids
        }
        val task = FutureTask<ArrayList<Int>>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone){}
        return ids
    }


    // получение полного списка упражнений с мышцами для адаптера
    public fun getListData() : List<List<ExerciseList>>{
        val listData = ArrayList<List<ExerciseList>>()
        val r = Callable<List<List<ExerciseList>>>() {
            db = AppDatabase.getDatabase(context);
            val muscle: List<Muscle>? = db?.MuscleDao()?.getAll()
            if (muscle != null) {
                for (mus in muscle) {
                    var ex: List<ExerciseList>? = null
                    if (mus.ID_Muscle != null) {
                        ex = db?.ExerciseListDao()?.getInMuscle(mus.ID_Muscle!!)
                    }
                    if (ex != null) listData.add(ex)
                }
            }
            return@Callable listData
        }
        val task = FutureTask<List<List<ExerciseList>>>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone){}
        return listData
    }

    public fun isThereNoAppr(tr_id: Int):Boolean {
        var f: Boolean = false
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val ex_list = db?.ExerciseDao()?.getInTrainingByID(tr_id)
            if (ex_list != null && ex_list.size != 0) {
                Log.d("Ex", "Ex_list")
                for (ex in ex_list){
                    val appr_list = ex.ID_Ex?.let { db?.ApproachDao()?.getInExByID(it) }
                    if (appr_list != null && appr_list.size != 0){
                       for(appr in appr_list){
                           if (appr.weight == null || appr.repeat == null){
                               f = true
                               break;
                           }
                       }
                        if (f) break
                    } else{
                        f = true
                        break
                    }
                }
            } else{
                f = true
            }
        }
        t.start()
        t.join()
        return  f
    }

    public fun addNewExList(name: String, desc: String?){
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val ex = ExerciseList(null, 9, name, desc)
            db?.ExerciseListDao()?.insert(ex)
        }
        t.start()
    }

    //получение имени упражнения
    public fun getExName(ex: Exercise?) : String? {
        var name:String? = null
        val r = Callable<String> {
            db = AppDatabase.getDatabase(context);
            val trl : ExerciseList? = ex?.ExList_ID?.let { db?.ExerciseListDao()?.getById(it) }
            if (trl != null) {
                name = trl.name
            }
            return@Callable name
        }
        val task = FutureTask<String>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone()){}
        return name
    }

    public fun deleteExFromTraining(ex: Exercise?){
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            if (ex != null) {
                db?.ExerciseDao()?.delete(ex)
            }
        }
        t.start()
    }

    public fun deleteApprFromEx(appr: Approach?){
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            if (appr != null) {
                db?.ApproachDao()?.delete(appr)
            }
        }
        t.start()
    }


    //получение количества подходов упражнения
    public fun getApprKolFromEx(currentItem: Exercise?) : Int? {
        var kol:Int? = null
        val r = Callable<Int> {
            db = AppDatabase.getDatabase(context);
            val list_appr = currentItem?.ID_Ex?.let { db?.ApproachDao()?.getInExByID(it) }
            if (list_appr != null) {
                kol = list_appr.size
            }
            return@Callable kol
        }
        val task = FutureTask<Int>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone()){}
        return kol
    }

    //получение списка количества подходов упражнений в тренировке по в
    public fun getApprKolListFromTr(tr_id: Int) : List<Int> {
        val kol_list: ArrayList<Int> = ArrayList()
        val r = Callable<ArrayList<Int>> {
            db = AppDatabase.getDatabase(context);
            val ex_list = db?.ExerciseDao()?.getInTrainingByID(tr_id)
            for (ex in ex_list!!){
                val list_appr = ex.ID_Ex?.let { db?.ApproachDao()?.getInExByID(it) }
                if (list_appr != null) {
                    kol_list.add(list_appr.size)
                }
            }
            return@Callable kol_list
        }
        val task = FutureTask<ArrayList<Int>>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone()){}
        return kol_list as List<Int>
    }

    //получение списка количества подходов упражнений в тренировке по в
    public fun getDoneApprKolListFromTr(tr_id: Int) : List<Int> {
        val kol_list: ArrayList<Int> = ArrayList()
        val r = Callable<ArrayList<Int>> {
            db = AppDatabase.getDatabase(context);
            val ex_list = db?.ExerciseDao()?.getInTrainingByID(tr_id)
            for (ex in ex_list!!){
                val list_appr = ex.ID_Ex?.let { db?.ApproachDao()?.getInExByID(it) }
                if (list_appr != null) {
                    kol_list.add(0)
                }
            }
            return@Callable kol_list
        }
        val task = FutureTask<ArrayList<Int>>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone()){}
        return kol_list as List<Int>
    }



    //получение списка эффективности всех тренировок
    public fun getAllEffency() : List<Efficiency>? {
        var list: List<Efficiency>? = null
        val r = Callable<List<Efficiency>?> {
            db = AppDatabase.getDatabase(context);
            list = db?.EfficiencyDao()?.getAll()
            return@Callable list
        }
        val task = FutureTask<List<Efficiency>?>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone()){}
        return list
    }

    //получение названия тренировки по её эффективности
    public fun getTrNameByEff(eff: Efficiency?) : String? {
        var name: String? = null
        val r = Callable<String? > {
            db = AppDatabase.getDatabase(context);
            val tr = eff?.Training_ID?.let { db?.TrainingDao()?.getById(it) }
            if (tr != null) {
                name = tr.name
            }
            return@Callable name
        }
        val task = FutureTask<String?>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone()){}
        return name
    }

    public fun getDateByEff(eff: Efficiency?) : String? {
        var date: String? = null
        val r = Callable<String? > {
            db = AppDatabase.getDatabase(context);
            val d = eff?.Date_ID?.let { db?.ExDateDao()?.getById(it) }
            var m: String ?= null
            if (d?.month!! < 10) m ="0" + (d?.month?.plus(1)).toString()
            date = d?.day.toString() + "." + m + "." + d?.year.toString()
            return@Callable date
        }
        val task = FutureTask<String?>(r)
        Executors.newSingleThreadExecutor().execute(task)
        while (!task.isDone()){}
        return date
    }


    public fun getDescFromEx(ex: Exercise): String?{
        var desc : String? = null
        val t = Thread {
            db = AppDatabase.getDatabase(context);
            val exlist = db?.ExerciseListDao()?.getById(ex.ExList_ID)
            if (exlist != null) {
                desc = exlist.desc
            }
        }
        t.start()
        t.join()
        return desc
    }

    //создание пустой тренировки по умолчанию
    public fun createEmptyTraining() : Int {
        var id: Int = 0
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val tr: Training? = Training(null, "Новая")
            if (tr != null) {
                db?.TrainingDao()?.insert(tr)
            }
            id = db?.TrainingDao()?.getAll()?.last()?.ID_Training!!
        }
        t.start()
        t.join();
        return id
    }

    //получение имени тренировки
    public fun getTrainingName(id:Int) : String? {
        var st: String ?= null
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val tr: Training? = db?.TrainingDao()?.getById(id)
            if (tr != null) {
                st = tr.name
            }
        }
        t.start()
        t.join()
        return st
    }

    public fun getExName(id:Int) : String? {
        var st: String ?= null
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val ex: Exercise? = db?.ExerciseDao()?.getById(id)
            if (ex != null) {
                val exlist = db?.ExerciseListDao()?.getById(ex.ExList_ID)
                if (exlist != null) {
                    st = exlist.name
                }
            }
        }
        t.start()
        t.join()
        return st
    }

    //изменение имени тренировки
    public fun changeTrainingName(id:Int, name:String)  {
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            var tr: Training? = db?.TrainingDao()?.getById(id)
            if (tr != null) {
                tr.name = name
            }
            if (tr != null) {
                db?.TrainingDao()?.update(tr)
            }
        }
        t.start()
    }

    //получение списка упражнений тренировки
    public fun getAllExByTraining(id: Int) : List<Exercise>?{
        var list: List<Exercise>? = null
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            list = db?.ExerciseDao()?.getInTrainingByID(id)
        }
        t.start()
        t.join()
        return list
    }

    //добавление упражнений в тренировку по спику id ExerciseList
    public fun addArrayExToTraining(ex_id_list:ArrayList<Int>?, id: Int?){
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            if (ex_id_list != null) {
                for (ex_id in ex_id_list){
                    Log.d("In In In", ex_id.toString())
                    //проверяем, было ли такое упражнение в тренировке
                    var ex = id?.let { db?.ExerciseDao()?.getByExListAndTrainingId(ex_id, it) }
                    if (ex == null){
                        ex = id?.let { Exercise(null, it, ex_id) }
                        if (ex != null) {
                            db?.ExerciseDao()?.insert(ex)
                        }
                    }
                }
            }
        }
        t.start()
        t.join()
    }

    //добавление одного упражнения в тренировку по  id
    public fun addExToTraining(ex_id: Int?, tr_id: Int?){
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            //проверяем, было ли такое упражнение в тренировке
            if (ex_id!=null && tr_id!=null){
                var ex = db?.ExerciseDao()?.getByExListAndTrainingId(ex_id, tr_id)
                if (ex == null){
                    ex = Exercise(null, tr_id, ex_id)
                    if (ex != null) {
                        db?.ExerciseDao()?.insert(ex)
                    }
                }
            }
        }
        t.start()
    }

    //удаление одного упражнения из тренировку по id
    public fun deleteExListFromTraining(ex_id: Int?, tr_id: Int?){
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            //проверяем, было ли такое упражнение в тренировке
            if (ex_id!=null && tr_id!=null){
                val ex = db?.ExerciseDao()?.getByExListAndTrainingId(ex_id, tr_id)
                if (ex != null){
                    db?.ExerciseDao()?.delete(ex)
                }
            }
        }
        t.start()
    }


    //получение списка упражнений тренировки
    public fun getAllExListByTraining(id: Int) : List<ExerciseList>{
        val list = ArrayList<ExerciseList>()
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val exlist = db?.ExerciseDao()?.getInTrainingByID(id)
            if (exlist != null) {
                for (ex in exlist){
                    val exl = db?.ExerciseListDao()?.getById(ex.ExList_ID)
                    if (exl != null) {
                        list.add(exl)
                    }
                }
            }

        }
        t.start()
        t.join()
        return list as List<ExerciseList>
    }

    public fun addApprToEx(appr: Approach){
        val t = Thread {
            db = AppDatabase.getDatabase(context);
            db?.ApproachDao()?.insert(appr)
        }
        t.start()
        t.join()
    }

    public fun addApprToEx(list:ArrayList<Pair<Int?, Int?>>, ex_id:Int?){
        val t = Thread {
            db = AppDatabase.getDatabase(context);
            val list_for_del = ex_id?.let { db?.ApproachDao()?.getInExByID(it) }
            if (list_for_del != null) {
                for (del in list_for_del){
                    db?.ApproachDao()?.delete(del)
                }
            }
            for (el in list){
                val appr = ex_id?.let { Approach(null, it, el.second, el.first) }
                if (appr != null) {
                    db?.ApproachDao()?.insert(appr)
                }
            }
        }
        t.start()
    }

    public fun getAllApprFromEx(ex_id:Int?): List<Approach>?{
        var appr_list :List<Approach>?=null
        val t = Thread {
            db = AppDatabase.getDatabase(context);
            appr_list = ex_id?.let { db?.ApproachDao()?.getInExByID(it) }
        }
        t.start()
        t.join()
        return appr_list
    }

    //заполнение даты в базе
    public fun addDate(): Int{
        var id: Int = 0
        val calendar: Calendar = Calendar.getInstance()
        val day = calendar.get(Calendar.DAY_OF_MONTH)
        val month = calendar.get(Calendar.MONTH)
        val year = calendar.get(Calendar.YEAR)
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            var today = db?.ExDateDao()?.getByDate(day, month, year)
            if (today == null){
                today = ExDate(null, day, month, year)
                db?.ExDateDao()?.insert(today)
                today = db?.ExDateDao()?.getAll()?.last()
            }
            if (today != null) {
                id = today.ID_Date!!
            }
        }
        t.start()
        t.join()
        return id
    }

    public fun setEfficiency(tr_id: Int, date_id: Int, time: Int, per: Int){
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            var eff = Efficiency(null, tr_id, date_id, time, per)
            db?.EfficiencyDao()?.insert(eff)
        }
        t.start()
    }

    public fun getMaxFilling(tr_id: Int): Int{
        var kol : Int = 0
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val ex_list = db?.ExerciseDao()?.getInTrainingByID(tr_id)
            if (ex_list != null) {
                for (ex in ex_list){
                    val id = ex.ID_Ex
                    val appr_list = id?.let { db?.ApproachDao()?.getInExByID(it) }
                    if (appr_list != null) {
                        for (appr in appr_list){
                            if (appr.weight != 0){
                                kol = kol + appr.repeat!! * appr.weight!!
                            } else{
                                kol += appr.repeat!!
                            }
                        }
                    }
                }
            }

        }
        t.start()
        t.join()
        return kol
    }

    // удаление эффективности из списка
    public fun deleteEff(eff: Efficiency?) {
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            if (eff != null) {
                db?.EfficiencyDao()?.delete(eff)
            }
        }
        t.start()
        t.join()
    }

    // удаление всего списка эффективности
    public fun deleteAllEff() {
        val t = Thread{
            db = AppDatabase.getDatabase(context);
            val list : List<Efficiency>? = db?.EfficiencyDao()?.getAll()
            if (list != null) {
                for (eff in list){
                    db?.EfficiencyDao()?.delete(eff)
                }
            }
        }
        t.start()
        t.join()
    }

}