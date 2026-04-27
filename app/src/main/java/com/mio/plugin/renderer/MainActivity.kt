package com.mio.plugin.renderer

import android.app.Activity
import android.graphics.Color
import android.os.Bundle
import android.widget.LinearLayout
import android.widget.TextView
import com.mio.plugin.renderer.core.MaliBridgeCore

class MainActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        MaliBridgeCore.initialize()

        val layout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setPadding(32, 32, 32, 32)
            setBackgroundColor(Color.parseColor("#1a1a2e"))
        }

        layout.addView(TextView(this).apply {
            text = "⚡ MaliBridge — EngenhariaSonora"
            textSize = 22f
            setTextColor(Color.parseColor("#FFD700"))
        })

        layout.addView(TextView(this).apply {
            text = MaliBridgeCore.generateReport()
            textSize = 14f
            setTextColor(Color.WHITE)
        })

        setContentView(layout)
    }
}
