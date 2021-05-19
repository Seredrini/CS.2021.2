package com.example.myapplication

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication.Adapter.CardApprAdapter
import com.example.myapplication.DataBase.DBCall
import com.google.android.material.floatingactionbutton.FloatingActionButton

class ApproachListActivity : AppCompatActivity() {

    lateinit var recycler : RecyclerView
    lateinit var add_b: FloatingActionButton
    var id : Int? = null
    var ex_id : Int? = null
    lateinit var list: ArrayList<Pair<Int?, Int?>>
    lateinit var name: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_approach_list)
        setTitle("Подходы")
        getSupportActionBar()?.setDisplayHomeAsUpEnabled(true)

        add_b = findViewById(R.id.add_button)
        name = findViewById(R.id.info)
        val db_call = DBCall(this.applicationContext)
        id = intent.extras?.get("id") as Int?
        ex_id = intent.extras?.get("ex_id") as Int?

        name.text = ex_id?.let { db_call.getExName(it) }

        recycler =  findViewById(R.id.recycler_view)
        recycler.adapter = CardApprAdapter(ex_id!!, this@ApproachListActivity.applicationContext)
        recycler.layoutManager = LinearLayoutManager(this@ApproachListActivity)
        recycler.setHasFixedSize(true)
        recycler.itemAnimator = null

        add_b.setOnClickListener{
            (recycler.adapter as CardApprAdapter).addNewApp()
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
                (recycler.adapter as CardApprAdapter).notifyDataSetChanged()
                val i = Intent(this, CreateTrainingActivity::class.java)
                i.putExtra("id", id)
                startActivity(i)
            }
        }
        return super.onOptionsItemSelected(item)
    }
}