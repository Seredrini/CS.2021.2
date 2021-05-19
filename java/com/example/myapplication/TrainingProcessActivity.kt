package com.example.myapplication

import Adapter.CardProcessAdapter
import android.content.Intent
import android.os.Bundle
import android.os.SystemClock
import android.view.Menu
import android.view.MenuItem
import android.widget.Chronometer
import android.widget.ImageButton
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication.DataBase.DBCall
import com.example.myapplication.Entity.Approach
import com.example.myapplication.Entity.Exercise

class TrainingProcessActivity : AppCompatActivity() {

    lateinit var recycler : RecyclerView
    lateinit var chronometer: Chronometer
    lateinit var ok: ImageButton
    lateinit var weight: TextView
    lateinit var repeat: TextView
    lateinit var appr_name: TextView
    lateinit var db_call: DBCall

    //данные для отображения истории
    var tr_time : Int = 0
    var percent: Int = 0
    var current_filling: Int = 0
    var max_filling: Int? = null
    var id: Int? = null
    var day_id: Int? = null

    //данные для отображения подходов
    var appr_list : List<Approach> ?= null
    var ex_list: List<Exercise>? = null
    var ex_is_done: Array<Boolean?> ?= null
    var ex_num: Int = 0
    var appr_num: Int = 0
    var max_appr_num: Int = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_training_process)
        getSupportActionBar()?.setDisplayHomeAsUpEnabled(true)

        id = intent.extras?.get("id") as Int?
        ok = findViewById(R.id.ok)
        weight = findViewById(R.id.weight)
        repeat = findViewById(R.id.repeat)
        appr_name = findViewById(R.id.appr_number)
        db_call = DBCall(this.applicationContext)

        var tr_name : String? = "Тренировка"
        tr_name = id?.let { db_call.getTrainingName(it) }
        setTitle(tr_name)

        day_id = db_call.addDate()
        max_filling = id?.let { db_call.getMaxFilling(it) }

        //запуск секундомера
        chronometer = findViewById(R.id.simpleChronometer)
        chronometer.base = SystemClock.elapsedRealtime()
        chronometer.start()

        //подключение адаптера
        recycler =  findViewById(R.id.recycler_view)
        recycler.adapter = id?.let { CardProcessAdapter(it, this@TrainingProcessActivity.applicationContext) }
        recycler.layoutManager = LinearLayoutManager(this@TrainingProcessActivity)
        recycler.setHasFixedSize(true)

        //работа с подходами и упражнениями
        ex_list = id?.let { db_call.getAllExByTraining(it) }
        appr_list = db_call.getAllApprFromEx(ex_list?.get(ex_num)?.ID_Ex)
        ex_is_done = arrayOfNulls(ex_list!!.size)

        beginEx(0, 0)

        ok.setOnClickListener {

            if (appr_name.text == "Тренировка завершена"){
                endTraining()
            }
            if (appr_name.text == "Упражнение завершено"){
                NextEx(ex_num)
            }
            else{
                saveDateFromView()

                if (appr_num+1 <= max_appr_num) {
                    (recycler.adapter as CardProcessAdapter).changeDoneKolAppr(ex_num)
                    appr_num += 1
                    setApprOnView()

                } else if (ex_list != null) {
                    ex_is_done!!.set(ex_num, true)
                    (recycler.adapter as CardProcessAdapter).changeDoneKolAppr(ex_num)
                    NextEx(ex_num)
                }
            }

        }
    }


    fun endTraining(){
        val elapsedMillis: Long = (SystemClock.elapsedRealtime() - chronometer.base)
        tr_time = (elapsedMillis / 1000 / 60).toInt()
        chronometer.stop()
        if (max_filling!= 0){
            percent = current_filling * 100 / max_filling!!
        }
        else{
            percent = 0
        }
        val db_call = DBCall(this.applicationContext)
        db_call.setEfficiency(id!!, day_id!!, tr_time, percent)
        val i = Intent(this, TrainingListActivity::class.java)
        startActivity(i)
    }

    fun exIsDone(position: Int){
        ex_num = position
        val st: String = "Упражнение завершено"
        appr_name.text = st
        weight.text = ""
        repeat.text = ""
    }

    fun NextEx(ex_num: Int){
        val ex_num = getNextPosition(ex_num)
        if (ex_num != -1){
            val appr = (recycler.adapter as CardProcessAdapter).getDoneKolAppr(ex_num)
            beginEx(ex_num, appr)
        }
        else{
            val st: String = "Тренировка завершена"
            appr_name.text = st
        }
    }

    fun setApprOnView(){
        val st: String = "Подход " + appr_num.toString()
        appr_name.text = st
        weight.text = appr_list?.get(appr_num-1)?.weight.toString()
        repeat.text = appr_list?.get(appr_num-1)?.repeat.toString()
    }

    fun saveDateFromView(){
        val w : Int = weight.text.toString().toInt()
        val r : Int = repeat.text.toString().toInt()
        if (w != 0){
            current_filling += w*r
        } else{
            current_filling += r
        }
    }

    fun beginEx(position: Int, done_kol_appr: Int){
        ex_num = position
        appr_num = done_kol_appr + 1
        appr_list = db_call.getAllApprFromEx(ex_list?.get(ex_num)?.ID_Ex)
        max_appr_num = appr_list?.size ?: 0
        setApprOnView()
        (recycler.adapter as CardProcessAdapter).changeColorOnPosition(ex_num)
    }

    fun getNextPosition(ex_num: Int): Int{
        if (ex_num + 1 < ex_list!!.size && ex_is_done?.get(ex_num+1) == null){
            return ex_num + 1
        }
        var pos = ex_num + 2
        while(pos < ex_list!!.size){
            if (ex_is_done?.get(pos) == null) return pos
            pos += 1
        }
        pos = 0
        while(pos < ex_num){
            if (ex_is_done?.get(pos) == null) return pos
            pos += 1
        }
        return -1
    }


    // кнопка сохранить в меню
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        getMenuInflater().inflate(R.menu.activity_menu, menu);
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            android.R.id.home -> {
                finish()
                return true
            }
            else -> {
                endTraining()
            }
        }
        return super.onOptionsItemSelected(item)
    }

}