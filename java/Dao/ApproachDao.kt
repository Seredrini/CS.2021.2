package com.example.myapplication.Dao
import androidx.room.*
import com.example.myapplication.Entity.Approach
import com.example.myapplication.Entity.Exercise

@Dao
interface ApproachDao {
    @Insert (onConflict = OnConflictStrategy.REPLACE)
    fun insert (app: Approach);

    @Update
    fun update (app: Approach)

    @Delete
    fun delete (app: Approach)

    @Query ("SELECT * FROM Approach")
    fun getAll(): List <Approach>

    @Query ("SELECT * FROM Approach WHERE ID_App = :id")
    fun getById(id: Int): Approach

    @Query("SELECT * FROM Approach WHERE Ex_ID = :id")
    fun getInExByID(id: Int): List <Approach>

}