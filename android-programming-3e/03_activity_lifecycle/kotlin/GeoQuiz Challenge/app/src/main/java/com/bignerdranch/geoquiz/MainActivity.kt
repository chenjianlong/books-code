package com.bignerdranch.geoquiz

import android.os.Bundle
import android.util.Log
import android.view.Gravity
import android.widget.Button
import android.widget.ImageButton
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlin.concurrent.thread

class MainActivity : AppCompatActivity() {
    private lateinit var trueBtn: Button
    private lateinit var falseBtn: Button
    private lateinit var prevBtn: ImageButton
    private lateinit var nextBtn: ImageButton
    private lateinit var questionTextView: TextView
    private val questionBank = listOf(
        Question(R.string.question_australia, true),
        Question(R.string.question_oceans, true),
        Question(R.string.question_mideast, false),
        Question(R.string.question_africa, false),
        Question(R.string.question_americas, true),
        Question(R.string.question_asia, true)
    )

    private val answerBank = HashMap<Int, Boolean>()
    private var currentIndex = 0
    private val TAG = "QuizActivity"
    private val KEY_INDEX = "index"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d(TAG, "onCreate(Bundle) called")
        setContentView(R.layout.activity_main)
        questionTextView = findViewById(R.id.question_text_view)
        trueBtn = findViewById(R.id.true_button)
        falseBtn = findViewById(R.id.false_button)
        prevBtn = findViewById(R.id.prev_button)
        nextBtn = findViewById(R.id.next_button)
        trueBtn.setOnClickListener {
            checkAnswer(true)
        }

        falseBtn.setOnClickListener {
            checkAnswer(false)
        }

        prevBtn.setOnClickListener {
            --currentIndex
            if (currentIndex < 0) {
                currentIndex = questionBank.size - 1
            }

            updateQuestion()
        }

        nextBtn.setOnClickListener {
            currentIndex = (currentIndex + 1) % questionBank.size
            updateQuestion()
        }

        questionTextView.setOnClickListener {
            currentIndex = (currentIndex + 1) % questionBank.size
            updateQuestion()
        }

        savedInstanceState?.let {
            currentIndex = it.getInt(KEY_INDEX)
        }

        updateQuestion()
    }

    override fun onStart() {
        super.onStart()
        Log.d(TAG, "onStart() called")
    }

    override fun onResume() {
        super.onResume()
        Log.d(TAG, "onResume() called")
    }

    override fun onPause() {
        super.onPause()
        Log.d(TAG, "onPause() called")
    }

    override fun onStop() {
        super.onStop()
        Log.d(TAG, "onStop() called")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d(TAG, "onDestroy() called")
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        Log.d(TAG, "onSaveInstanceState() called")
        outState.putInt(KEY_INDEX, currentIndex)
    }

    private fun updateQuestion() {
        questionTextView.setText(questionBank[currentIndex].textResId)
        val isEnabled = !answerBank.containsKey(currentIndex)
        trueBtn.isEnabled = isEnabled
        falseBtn.isEnabled = isEnabled
    }

    private fun checkAnswer(userPressedTrue: Boolean) {
        val answerIsTrue = questionBank[currentIndex].answerTrue
        val messageResId = if (userPressedTrue == answerIsTrue) {
            answerBank[currentIndex] = true
            R.string.correct_toast
        } else {
            answerBank[currentIndex] = false
            R.string.incorrect_toast
        }

        Toast.makeText(this, messageResId, Toast.LENGTH_SHORT).show()
        updateQuestion()
        checkScore()
    }

    private fun checkScore() {
        if (answerBank.size == questionBank.size) {
            var correctAnswers: Int = 0
            for ((_, isCorrect) in answerBank) {
                if (isCorrect) {
                    correctAnswers++
                }
            }
            val score = Math.round(correctAnswers.toDouble() / answerBank.size * 100).toInt()
            val scoreText = applicationContext.resources.getString(R.string.quiz_score, score)
            Toast.makeText(this, scoreText, Toast.LENGTH_LONG).show()
        }
    }
}