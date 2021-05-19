package com.example.myapplication.Dao
import androidx.room.*
import com.example.myapplication.Entity.ExDate

@Dao
interface ExDateDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert (date: ExDate);

    @Update
    fun update (date: ExDate)

    @Delete
    fun delete (date: ExDate)

    @Query("SELECT * FROM ExDate")
    fun getAll(): List <ExDate>

    @Query("SELECT * FROM ExDate WHERE ID_Date = :id")
    fun getById(id: Int): ExDate

    @Query("SELECT * FROM ExDate WHERE Day = :d AND Month = :m AND Year = :y")
    fun getByDate(d: Int, m:Int, y:Int): ExDate
}