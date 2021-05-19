package com.example.myapplication.DataBase
import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import com.example.myapplication.Dao.*
import com.example.myapplication.Entity.*

@Database (entities = [Approach::class , Exercise::class, ExDate::class,
                    ExerciseList::class, Muscle::class,
                    Training::class, Efficiency::class ], version = 2, exportSchema = true)
abstract class AppDatabase : RoomDatabase() {
    abstract fun ApproachDao() : ApproachDao
    abstract fun ExerciseDao(): ExerciseDao
    abstract fun ExerciseListDao(): ExerciseListDao
    abstract fun TrainingDao(): TrainingDao
    abstract fun MuscleDao(): MuscleDao
    abstract fun ExDateDao(): ExDateDao
    abstract fun EfficiencyDao(): EfficiencyDao

    companion object{
        @Volatile
        private var instance: AppDatabase? = null

        fun getDatabase(context: Context) : AppDatabase? {
            if (instance == null){
                instance = Room.databaseBuilder(context, AppDatabase::class.java, "training_db.db").createFromAsset("my_training.db").build()
                val db = getDatabase(context)
            }
            return instance
        }
    }
}