package com.example.myapplication

import Adapter.CardHistoryAdapter
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication.DataBase.DBCall

class HistoryActivity : AppCompatActivity() {

    lateinit var recycler : RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_history)
        setTitle("История тренировок")
        getSupportActionBar()?.setDisplayHomeAsUpEnabled(true)

        //подключение адаптера
        recycler =  findViewById(R.id.recycler_view)
        recycler.adapter = CardHistoryAdapter(this@HistoryActivity.applicationContext)
        recycler.layoutManager = LinearLayoutManager(this@HistoryActivity)
        recycler.setHasFixedSize(true)
    }

    // кнопка очистить историю
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        getMenuInflater().inflate(R.menu.history_menu, menu);
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            android.R.id.home -> {
                finish()
                return true
            }
            else -> {
                val db_call = DBCall(this.applicationContext)
                db_call.deleteAllEff()
                (recycler.adapter as CardHistoryAdapter).update()
            }
        }
        return super.onOptionsItemSelected(item)
    }
}