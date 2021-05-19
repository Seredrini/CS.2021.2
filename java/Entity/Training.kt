package com.example.myapplication.Entity
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class Training (
    @PrimaryKey (autoGenerate = true) var ID_Training: Int?,
    @ColumnInfo (name = "Name") var name: String?
)

