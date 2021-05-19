package com.example.myapplication.Entity
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
class Muscle (
    @PrimaryKey (autoGenerate = true) var ID_Muscle:Int?,
    var name: String
)