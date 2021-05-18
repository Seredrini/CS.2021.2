package com.example.myapplication.Dao

import androidx.room.*
import com.example.myapplication.Entity.Training

@Dao
interface TrainingDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert (tr: Training);

    @Update
    fun update (tr: Training)

    @Delete
    fun delete (tr: Training)

    @Query("SELECT * FROM Training")
    fun getAll(): List <Training>

    @Query("SELECT * FROM Training WHERE ID_Training = :id")
    fun getById(id: Int): Training

}