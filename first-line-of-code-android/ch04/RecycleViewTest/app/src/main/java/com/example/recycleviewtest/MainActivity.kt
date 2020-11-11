package com.example.recycleviewtest

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.StaggeredGridLayoutManager
import com.example.listviewtest.Fruit
import com.example.recycleviewtest.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private val fruitList = ArrayList<Fruit>()
    private lateinit var binding: ActivityMainBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)
        initFruits()
        val layoutManager = StaggeredGridLayoutManager(3, StaggeredGridLayoutManager.VERTICAL)
        binding.recycleView.layoutManager = layoutManager
        val adapter = FruitAdapter(fruitList)
        binding.recycleView.adapter = adapter
    }

    private fun initFruits() {
        /*repeat(2) {
            fruitList.add(Fruit("Apple", R.drawable.apple_pic))
            fruitList.add(Fruit("Banana", R.drawable.banana_pic))
            fruitList.add(Fruit("Orange", R.drawable.orange_pic))
            fruitList.add(Fruit("WaterMelon", R.drawable.watermelon_pic))
            fruitList.add(Fruit("Pear", R.drawable.pear_pic))
            fruitList.add(Fruit("Grape", R.drawable.grape_pic))
            fruitList.add(Fruit("Pineapple", R.drawable.pineapple_pic))
            fruitList.add(Fruit("Strawberry", R.drawable.strawberry_pic))
            fruitList.add(Fruit("Cherry", R.drawable.cherry_pic))
            fruitList.add(Fruit("Mango", R.drawable.mango_pic))
        }*/

        repeat(2) {
            fruitList.add(Fruit(getRandomLengthString("Apple"), R.drawable.apple_pic))
            fruitList.add(Fruit(getRandomLengthString("Banana"), R.drawable.banana_pic))
            fruitList.add(Fruit(getRandomLengthString("Orange"), R.drawable.orange_pic))
            fruitList.add(Fruit(getRandomLengthString("WaterMelon"), R.drawable.watermelon_pic))
            fruitList.add(Fruit(getRandomLengthString("Pear"), R.drawable.pear_pic))
            fruitList.add(Fruit(getRandomLengthString("Grape"), R.drawable.grape_pic))
            fruitList.add(Fruit(getRandomLengthString("Pineapple"), R.drawable.pineapple_pic))
            fruitList.add(Fruit(getRandomLengthString("Strawberry"), R.drawable.strawberry_pic))
            fruitList.add(Fruit(getRandomLengthString("Cherry"), R.drawable.cherry_pic))
            fruitList.add(Fruit(getRandomLengthString("Mango"), R.drawable.mango_pic))
        }
    }

    private fun getRandomLengthString(str: String): String {
        val n = (1..20).random()
        val builder = StringBuilder()
        repeat(n) {
            builder.append(str)
        }
        return builder.toString()
    }
}