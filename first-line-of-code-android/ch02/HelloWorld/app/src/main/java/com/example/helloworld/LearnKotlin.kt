package com.example.helloworld

import java.lang.StringBuilder
import kotlin.math.max

/*fun largerNumber(num1: Int, num2: Int): Int {
    //return max(num1, num2)
    return if (num1 > num2) {
        num1
    } else {
        num2
    }
}*/

//fun largerNumber(num1: Int, num2: Int): Int = max(num1, num2)
//fun largerNumber(num1: Int, num2: Int) = max(num1, num2)
fun largerNumber(num1: Int, num2: Int) = if (num1 > num2) {
    num1
} else {
    num2
}

/*fun getScore(name: String) = if (name == "Tom") {
    86
} else if (name == "Jim") {
    77
} else if (name == "Jack") {
    95
} else if (name == "Lily") {
    100
} else {
    0
}*/

/*fun getScore(name: String) = when (name) {
    "Tom" -> 86
    "Jim" -> 77
    "Jack" -> 95
    "Lily" -> 100
    else -> 0
}*/

fun getScore(name: String) = when {
    name.startsWith("Tom") -> 86
    name == "Jim" -> 77
    name == "Jack" -> 95
    name == "Lily" -> 100
    else -> 0
}

fun checkNumber(num: Number) {
    when (num) {
        is Int -> println("number is Int")
        is Double -> println("number is Double")
        else -> println("number not support")
    }
}

fun main() {
    //var a: Int = 10
    //a = a * 10
    //println("a = " + a)

    val a = 37
    val b = 40
    val value = largerNumber(a, b)
    println("larger number is " + value)
    println("Tommy's score is: " + getScore("Tommy"))
    println("Hello Kotlin!")

    val num = 10L
    checkNumber(num)

    for (i in 10 downTo -1 step 2) {
        println(i)
    }

    var s = Student("1234", 99)
    doStudy(s)

    val cellphone1 = Cellphone("Samsung", 1299.99)
    val cellphone2 = Cellphone("Samsung", 1299.99)
    println(cellphone1)
    println("cellphone1 equals cellphone2 " + (cellphone1 == cellphone2))
    Singleton.singletonTest()

    val list = mutableListOf("Apple", "Banana", "Orange", "Pear", "Grape")
    list.add("Watermelon")
    for (fruit in list) {
        println(fruit)
    }

    val maxLengthFruit = list.maxBy { it.length }
    println("maxLengthFruit: " + maxLengthFruit)
    val newList = list.filter { it.length <= 5 } .map { it.toUpperCase() }
    for (fruit in newList) {
        println(fruit)
    }

    /*val map = HashMap<String, Int>()
    map.put("Apple", 1)
    map.put("Banana", 2)
    map.put("Orange", 3)
    map.put("Pear", 4)
    map.put("Grape", 5)*/

    val map = mapOf("Apple" to 1, "Banana" to 2, "Orange" to 3, "Pear" to 4, "Grape" to 5)
    for ((fruit, number) in map) {
        println("fruit is " + fruit + ", number is " + number)
    }

    printParams(123)
    printParams(str = "world")

    /*val builder = StringBuilder()
    builder.append("Start eating fruits.\n")
    for (fruit in list) {
        builder.append(fruit).append("\n")
    }
    builder.append("Ate all fruits.")
    val result = builder.toString()*/
    val result = StringBuilder().apply {
        append("Start eating fruits.\n")
        for (fruit in list) {
            append(fruit).append("\n")
        }
        append("Ate all fruits.")
        //toString()
    }
    println(result)
    var count = "ABC123xyz!@#".lettersCount()
    println("string count is: $count")

    val money1 = Money(5)
    val money2 = Money(10)
    val money3 = money1 + money2
    println(money3.value)
    println((money3 + 20).value)
    println(+1)

    println("main start")
    var str = ""
    printString(str) { s ->
        println("lambda start")
        if (s.isEmpty()) return
        println(s)
        println("lambda end")
    }
    println("main end")
}

inline fun printString(str: String, block: (String) ->Unit) {
    println("printString begin")
    block(str)
    println("printString end")
}

fun doStudy(study: Study) {
    study.readBooks()
    study.doHomework()
}

fun printParams(num: Int = 100, str :String = "hello") {
    println("num is $num , str is $str")
}