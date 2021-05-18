package com.example.myapplication.Entity
import androidx.room.Entity
import androidx.room.ForeignKey
import androidx.room.PrimaryKey

@Entity (foreignKeys = [ ForeignKey(entity = Training::class,
        parentColumns = ["ID_Training"],
        childColumns = ["Training_ID"],
        onDelete = ForeignKey.CASCADE),
        ForeignKey(entity = ExerciseList::class,
        parentColumns = ["ID_ExList"],
        childColumns = ["ExList_ID"],
        onDelete = ForeignKey.CASCADE)
])

data class Exercise (
    @PrimaryKey (autoGenerate = true) var ID_Ex: Int?,

    var Training_ID: Int,
    var ExList_ID: Int
)