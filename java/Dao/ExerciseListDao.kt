package com.example.myapplication.Dao
import androidx.room.*
import com.example.myapplication.Entity.ExerciseList

@Dao
interface ExerciseListDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert (exlist: ExerciseList);

    @Update
    fun update (exlist: ExerciseList)

    @Delete
    fun delete (exlist: ExerciseList)

    @Query("SELECT * FROM ExerciseList")
    fun getAll(): List <ExerciseList>

    @Query("SELECT * FROM ExerciseList WHERE ID_ExList = :id")
    fun getById(id: Int): ExerciseList

    @Query("SELECT * FROM ExerciseList WHERE Name = :name")
    fun getByName(name: String): ExerciseList

    @Query("SELECT * FROM ExerciseList WHERE Muscle_ID = :id")
    fun getInMuscle(id: Int): List <ExerciseList>

    @Query("SELECT Name FROM ExerciseList WHERE Muscle_ID = :id")
    fun getNameInMuscle(id: Int): List <String>

}