package com.example.activitytest

import android.app.Activity
import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.Gravity
import android.view.Menu
import android.view.MenuItem
import android.widget.Button
import android.widget.Toast
import com.example.activitytest.databinding.FirstLayoutBinding

class FirstActivity : BaseActivity() {
    private lateinit var binding: FirstLayoutBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d("FirstActivity", "Task id is $taskId")
        //setContentView(R.layout.first_layout)
        binding = FirstLayoutBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)
        binding.button1.setOnClickListener {
            //Toast.makeText(this, "You clicked Button 1", Toast.LENGTH_SHORT).show()
            //finish()
            val data = "Hello SecondActivity"
            val intent = Intent(this, SecondActivity::class.java)
            //val intent = Intent(this, FirstActivity::class.java)
            startActivity(intent)
            //intent.putExtra("extra_data", data)
            //val intent = Intent("com.example.activitytest.ACTION_START")
            //intent.addCategory("com.example.activitytest.MY_CATEGORY")
            //val intent = Intent(Intent.ACTION_VIEW)
            //intent.data = Uri.parse("https://www.baidu.com")
            //val intent = Intent(Intent.ACTION_DIAL)
            //intent.data = Uri.parse("tel:10086")
            //startActivity(intent)
            //startActivityForResult(intent, 1)
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.add_item -> Toast.makeText(this, "You clicked Add", Toast.LENGTH_SHORT).show()
            R.id.remove_item -> Toast.makeText(this, "You clicked Remove", Toast.LENGTH_SHORT).show()
        }

        return true
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        when (requestCode) {
            1 -> if (resultCode == Activity.RESULT_OK) {
                val returnData = data?.getStringExtra("data_return")
                Log.d("FirstActivity", "returned data is $returnData")
            }
        }
    }

    override fun onRestart() {
        super.onRestart()
        Log.d("FirstActivity", "onRestart")
    }
}