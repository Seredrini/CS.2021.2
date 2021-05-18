package com.example.myapplication

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.TextView
import com.example.myapplication.DataBase.DBCall

class NewExerciseActivity : AppCompatActivity() {

    lateinit var name: TextView
    lateinit var desc: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_new_exercise)
        name = findViewById(R.id.name)
        desc = findViewById(R.id.desc)
        setTitle("Новое упражнение")
        getSupportActionBar()?.setDisplayHomeAsUpEnabled(true)
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
                val name_st : String? = name.text.toString()
                val desc_st : String? = desc.text.toString()
                val db_call = DBCall(this.applicationContext)
                if (name_st != null) {
                    db_call.addNewExList(name_st, desc_st)
                }
                val i = Intent(this, ExpandableExerciseListActivity::class.java)
                startActivity(i)
            }
        }
        return super.onOptionsItemSelected(item)
    }
}