package com.example.myapplication.Entity
import androidx.room.*
import androidx.room.ForeignKey.CASCADE

@Entity (tableName = "Approach",
        foreignKeys = [ ForeignKey(entity = Exercise::class,
                                parentColumns = ["ID_Ex"],
                                childColumns = ["Ex_ID"],
                                onDelete = CASCADE)])

data class Approach (
    @PrimaryKey (autoGenerate = true) var ID_App: Int?,

    @ColumnInfo (name = "Ex_ID") var Ex_ID: Int,
    @ColumnInfo (name = "Repaeat") var repeat: Int?,
    @ColumnInfo (name = "Weight") var weight: Int?

)

