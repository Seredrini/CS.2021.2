package com.example.myapplication.Dao
import androidx.room.*
import com.example.myapplication.Entity.Exercise

@Dao
interface ExerciseDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert (ex: Exercise);

    @Update
    fun update (ex: Exercise)

    @Delete
    fun delete (ex: Exercise)

    @Query("SELECT * FROM Exercise")
    fun getAll(): List <Exercise>

    @Query("SELECT * FROM Exercise WHERE Training_ID = :idt")
    fun getInTrainingByID(idt: Int): List <Exercise>

    @Query("SELECT * FROM Exercise WHERE ID_Ex = :id")
    fun getById(id: Int): Exercise

    @Query("SELECT * FROM Exercise WHERE ExList_ID = :id")
    fun getByExListId(id: Int): Exercise?

    @Query("SELECT * FROM Exercise WHERE ExList_ID = :ex_id AND Training_ID = :tr_id")
    fun  getByExListAndTrainingId(ex_id: Int, tr_id: Int): Exercise?


}