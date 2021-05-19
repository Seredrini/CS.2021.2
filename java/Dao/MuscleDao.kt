package com.example.myapplication.Dao
import androidx.room.*
import com.example.myapplication.Entity.Muscle

@Dao
interface MuscleDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert (mus: Muscle);

    @Update
    fun update (mus: Muscle)

    @Delete
    fun delete (mus: Muscle)

    @Query("SELECT * FROM Muscle")
    fun getAll(): List <Muscle>

    @Query("SELECT * FROM Muscle WHERE ID_Muscle = :id")
    fun getById(id: Int): Muscle
}