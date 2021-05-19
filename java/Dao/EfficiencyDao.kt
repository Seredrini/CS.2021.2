package com.example.myapplication.Dao
import androidx.room.*
import com.example.myapplication.Entity.Efficiency

@Dao
interface EfficiencyDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert (eff: Efficiency);

    @Update
    fun update (eff: Efficiency)

    @Delete
    fun delete (eff: Efficiency)

    @Query("SELECT * FROM Efficiency")
    fun getAll(): List <Efficiency>

    @Query("SELECT * FROM Efficiency WHERE ID_Eff = :id")
    fun getById(id: Int): Efficiency
}