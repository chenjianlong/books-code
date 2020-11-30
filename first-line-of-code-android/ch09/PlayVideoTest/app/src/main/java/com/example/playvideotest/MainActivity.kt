package com.example.playvideotest

import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.playvideotest.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        val uri = Uri.parse("android.resource://$packageName/${R.raw.video}")
        binding.videoView.setVideoURI(uri)
        binding.play.setOnClickListener {
            if (!binding.videoView.isPlaying) {
                binding.videoView.start()
            }
        }

        binding.pause.setOnClickListener {
            if (binding.videoView.isPlaying) {
                binding.videoView.pause()
            }
        }

        binding.replay.setOnClickListener {
            if (binding.videoView.isPlaying) {
                binding.videoView.resume()
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        binding.videoView.suspend()
    }
}