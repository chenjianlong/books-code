package com.example.activitytest

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.example.activitytest.databinding.ActivitySecondBinding
import com.example.activitytest.databinding.ThirdLayoutBinding

class ThirdActivity : BaseActivity() {
    private lateinit var binding: ThirdLayoutBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d("ThirdActivity", "Task id is $taskId")
        //setContentView(R.layout.third_layout)
        binding = ThirdLayoutBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)
        binding.button3.setOnClickListener {
            ActivityCollector.finishAll()
            android.os.Process.killProcess(android.os.Process.myPid())
        }
    }
}