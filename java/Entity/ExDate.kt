package com.example.myapplication.Entity
import androidx.room.ColumnInfo
import androidx.room.Dao
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class ExDate (
    @PrimaryKey (autoGenerate = true) var ID_Date: Int?,

    @ColumnInfo (name = "Day") var day: Int?,
    @ColumnInfo (name = "Month") var month: Int?,
    @ColumnInfo (name = "Year") var year: Int?
)