package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication.Adapter.CardExAdapter
import com.example.myapplication.DataBase.DBCall
import com.google.android.material.floatingactionbutton.FloatingActionButton

class CreateTrainingActivity : AppCompatActivity() {

    lateinit var add_ex: FloatingActionButton
    lateinit var name_view: TextView
    var name: String? = null
    var id: Int? = null
    lateinit var recycler : RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_create_training)
        setTitle("Тренировка")
        getSupportActionBar()?.setDisplayHomeAsUpEnabled(true)

        name_view = findViewById(R.id.weight)
        add_ex = findViewById(R.id.add_ex_button)
        val db_call = DBCall(this.applicationContext)

        val j = Intent(this, ExpandableExerciseListActivity::class.java)
        id = intent.extras?.get("id") as Int?
        Log.d("Id", id.toString())

        //создаём пустую тренировку, если она не создана
        if(id == null){
            id = db_call.createEmptyTraining()
            Log.d("IDD", id.toString())
        } else{
            name = db_call.getTrainingName(id!!)
        }

        // выставляем название тренировки
        if (name != null){
            name_view.setText(name)
        }

        //подключение адаптера
        recycler =  findViewById(R.id.recycler_view)
        recycler.adapter = CardExAdapter(id!!, this@CreateTrainingActivity.applicationContext)
        recycler.layoutManager = LinearLayoutManager(this@CreateTrainingActivity)
        recycler.setHasFixedSize(true)


        add_ex.setOnClickListener{
            //изменяем название тренировки
            name = name_view.text.toString()
            Log.d("Name 2", name.toString())
            db_call.changeTrainingName(id!!, name!!)

            //Переход в активность списка упражнений
            j.putExtra("id", id!!)
            startActivity(j)
        }
    }

    // кнопка сохранить в меню
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        getMenuInflater().inflate(R.menu.activity_menu, menu);
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            android.R.id.home -> {
                finish()
                return true
            }
            else -> {
                name = name_view.text.toString()
                val db_call = DBCall(this.applicationContext)
                val i = Intent(this, TrainingListActivity::class.java)
                id?.let { db_call.changeTrainingName(it, name!!) }
                startActivity(i)
            }
        }
        return super.onOptionsItemSelected(item)
    }
}