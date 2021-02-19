package com.bignerdranch.geoquiz

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Gravity
import android.widget.Button
import android.widget.Toast

class MainActivity : AppCompatActivity() {
    private lateinit var trueBtn: Button
    private lateinit var falseBtn: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        trueBtn = findViewById(R.id.true_button)
        falseBtn = findViewById(R.id.false_button)
        trueBtn.setOnClickListener {
            val toast = Toast.makeText(this, R.string.correct_toast, Toast.LENGTH_SHORT)
            toast.setGravity(Gravity.TOP, 0, 0)
            toast.show()
        }

        falseBtn.setOnClickListener {
            val toast =  Toast.makeText(this, R.string.incorrect_toast, Toast.LENGTH_SHORT)
            toast.setGravity(Gravity.TOP, 0, 0)
            toast.show()
        }
    }
}