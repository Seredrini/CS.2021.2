package com.example.myapplication.Entity
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.ForeignKey
import androidx.room.PrimaryKey

@Entity (foreignKeys = [ ForeignKey(entity = Muscle::class,
        parentColumns = ["ID_Muscle"],
        childColumns = ["Muscle_ID"],
        onDelete = ForeignKey.CASCADE
    )])

data class ExerciseList (
    @PrimaryKey (autoGenerate = true) var ID_ExList: Int?,

    @ColumnInfo (name = "Muscle_ID") var muscle_ID: Int,
    @ColumnInfo (name = "Name") var name:String,
    @ColumnInfo (name = "Description") var desc: String?
)