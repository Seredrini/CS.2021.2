package com.example.myapplication

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class MainActivity : AppCompatActivity() {

    lateinit var b: Button
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setTitle("Тренировочный план")

        b = findViewById(R.id.start)
        val i = Intent(this, TrainingListActivity::class.java)
        b.setOnClickListener{
            startActivity(i)
        }


    }
}