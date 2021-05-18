package com.example.myapplication

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.ExpandableListAdapter
import android.widget.ExpandableListView
import androidx.appcompat.app.AppCompatActivity
import com.example.myapplication.Adapter.CustomExpandableListAdapter
import com.google.android.material.floatingactionbutton.FloatingActionButton

class ExpandableExerciseListActivity : AppCompatActivity() {

    internal var adapter: ExpandableListAdapter? = null
    lateinit var expandableListView: ExpandableListView
    lateinit var add_ex: FloatingActionButton
    var id : Int? = null


    @SuppressLint("ResourceAsColor")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_expandable_exercise_list)
        setTitle("Список упражнений")
        getSupportActionBar()?.setDisplayHomeAsUpEnabled(true)

        expandableListView = findViewById(R.id.elv)
        add_ex = findViewById(R.id.add_ex_list)

        id = intent.extras?.get("id") as Int

        //подключение адаптера
        adapter = CustomExpandableListAdapter(this, id!!)
        expandableListView.setAdapter(adapter)

        add_ex.setOnClickListener {
            val i = Intent(this, NewExerciseActivity::class.java)
            startActivity(i)
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
                val p = Intent(this, CreateTrainingActivity::class.java)
                p.putExtra("id", id)
                startActivity(p)
            }
        }
        return super.onOptionsItemSelected(item)
    }

}