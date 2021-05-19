package com.example.myapplication.Entity
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.ForeignKey
import androidx.room.PrimaryKey

@Entity (foreignKeys = [ ForeignKey(entity = Training::class,
        parentColumns = ["ID_Training"],
        childColumns = ["Training_ID"],
        onDelete = ForeignKey.CASCADE),
    ForeignKey(entity = ExDate::class,
            parentColumns = ["ID_Date"],
            childColumns = ["Date_ID"],
            onDelete = ForeignKey.CASCADE)
])
data class Efficiency (
    @PrimaryKey (autoGenerate = true) var ID_Eff: Int?,

    var Training_ID: Int,
    var Date_ID: Int,
    var Time: Int?,
    var Percenr: Int?
)