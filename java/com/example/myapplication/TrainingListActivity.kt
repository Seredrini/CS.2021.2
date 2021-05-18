package com.example.myapplication

import android.content.Intent
import android.os.AsyncTask
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication.Adapter.CardAdapter
import com.example.myapplication.DataBase.AppDatabase
import com.example.myapplication.Entity.Training
import com.google.android.material.floatingactionbutton.FloatingActionButton


class TrainingListActivity : AppCompatActivity() {

    lateinit var add_b : FloatingActionButton
    lateinit var recycler : RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_training_list)
        setTitle("Тренировки")
        getSupportActionBar()?.setDisplayHomeAsUpEnabled(true)

        MyAsyncTask().execute()

        add_b = findViewById(R.id.add_button)
        recycler =  findViewById(R.id.recycler_view)

        val i = Intent(this, CreateTrainingActivity::class.java)
        add_b.setOnClickListener{
            startActivity(i)
        }

    }


    inner  class MyAsyncTask() : AsyncTask<Void, Void, List<Training>?>(){

        override fun doInBackground(vararg params: Void): List<Training>? {
            val db = AppDatabase.getDatabase(this@TrainingListActivity.applicationContext)
            val list : List <Training>? = db?.TrainingDao()?.getAll()
            return list
        }

        override fun onPostExecute(l: List<Training>?) {
            super.onPreExecute()
            recycler.adapter = CardAdapter(l, this@TrainingListActivity.applicationContext)
            recycler.layoutManager = LinearLayoutManager(this@TrainingListActivity)
            recycler.setHasFixedSize(true)
        }
  }

    // кнопка истории тренировок в меню
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        getMenuInflater().inflate(R.menu.activity_training_list_menu, menu);
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            android.R.id.home -> {
                finish()
                return true
            }
            else -> {
                val j = Intent(this, HistoryActivity::class.java)
                startActivity(j)
            }
        }
        return super.onOptionsItemSelected(item)
    }


}

