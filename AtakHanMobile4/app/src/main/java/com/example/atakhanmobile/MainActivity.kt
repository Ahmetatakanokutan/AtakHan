package com.example.atakhanmobile

import android.os.Bundle
import android.widget.Button
import android.util.Log
import android.widget.EditText
import android.widget.TextView
import android.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import com.example.myapp.R
import com.google.accompanist.systemuicontroller.rememberSystemUiController
import kotlinx.coroutines.*
import org.json.JSONObject
import java.io.OutputStream
import java.net.HttpURLConnection
import java.net.URL

class MainActivity : AppCompatActivity(), JoystickListener {

    private lateinit var planeEntity: PlaneEntity
    private var lastSentPlaneEntity: PlaneEntity? = null
    private var ipAddress: String? = null

    private lateinit var throttleTextView: TextView
    private lateinit var rudderTextView: TextView
    private lateinit var elevatorTextView: TextView
    private lateinit var ailerionRightTextView: TextView
    private lateinit var ailerionLeftTextView: TextView
    private lateinit var leftJoystick: JoystickView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        // Show IP input dialog only on first launch
        if (savedInstanceState == null) {
            showIpInputDialog()
        }

        // Initialize joysticks
        initializeJoysticks()

        // Initialize text views
        throttleTextView = findViewById(R.id.throttleTextView)
        rudderTextView = findViewById(R.id.rudderTextView)
        elevatorTextView = findViewById(R.id.elevatorTextView)
        ailerionRightTextView = findViewById(R.id.ailerionRightTextView)
        ailerionLeftTextView = findViewById(R.id.ailerionLeftTextView)

        // Initialize motor button
        val motorButton: Button = findViewById(R.id.motorButton)
        motorButton.setOnClickListener {
            leftJoystick.resetYAxis()
        }
    }

    private fun showIpInputDialog() {
        val dialogView = layoutInflater.inflate(R.layout.dialog_ip_input, null)
        val editTextIpAddress = dialogView.findViewById<EditText>(R.id.editTextIpAddress)

        AlertDialog.Builder(this).apply {
            setTitle("IP Adresi Girin")
            setView(dialogView)
            setCancelable(false)
            setPositiveButton("Tamam") { _, _ ->
                val enteredIpAddress = editTextIpAddress.text.toString()
                if (isValidIpAddress(enteredIpAddress)) {
                    ipAddress = enteredIpAddress
                } else {
                    showIpInputDialog()
                    return@setPositiveButton
                }
            }
            show()
        }
    }

    private fun isValidIpAddress(ip: String): Boolean {
        val regex = Regex(pattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$")
        return ip.matches(regex)
    }

    private fun initializeJoysticks() {
        planeEntity = PlaneEntity(throttle = "0", rudder = 0, elevator = 0, ailerionRight = 0, ailerionLeft = 0)
        lastSentPlaneEntity = planeEntity.copy()

        leftJoystick = findViewById(R.id.leftJoystick)
        val rightJoystick = findViewById<JoystickView>(R.id.rightJoystick)

        leftJoystick.setJoystickListener(this)
        rightJoystick.setJoystickListener(this)

        leftJoystick.isLeftJoystick = true
        leftJoystick.isHorizontalSnapBack = true
    }

    override fun onJoystickMoved(xPercent: Float, yPercent: Float, id: Int) {
        when (id) {
            R.id.leftJoystick -> {
                if (xPercent != 0f) {
                    planeEntity.rudder = (xPercent * 50).toInt()
                } else {
                    planeEntity.throttle = ((-yPercent + 1) * 50).toInt().toString()
                }
                if (xPercent == 0f) {
                    planeEntity.rudder = 0
                }
            }
            R.id.rightJoystick -> {
                planeEntity.elevator = (-yPercent * 50).toInt()
                planeEntity.ailerionRight = (xPercent * 50).toInt()
                planeEntity.ailerionLeft = (-xPercent * 50).toInt()
            }
        }
        updatePlaneDataUI()
        if (hasPlaneDataChanged()) {
            sendPlaneData()
        }
    }

    private fun updatePlaneDataUI() {
        throttleTextView.text = "Throttle: ${planeEntity.throttle}"
        rudderTextView.text = "Rudder: ${planeEntity.rudder}"
        elevatorTextView.text = "Elevator: ${planeEntity.elevator}"
        ailerionRightTextView.text = "Ailerion Right: ${planeEntity.ailerionRight}"
        ailerionLeftTextView.text = "Ailerion Left: ${planeEntity.ailerionLeft}"
    }

    private fun hasPlaneDataChanged(): Boolean {
        return planeEntity != lastSentPlaneEntity
    }

    private fun sendPlaneData() {
        val throttleValue = planeEntity.throttle.toIntOrNull()
        if (throttleValue != null && throttleValue in 0..100) {
            val url = "http://${ipAddress}:8080/api/plane/data"
            val jsonData = JSONObject().apply {
                put("throttle", throttleValue)
                put("rudder", planeEntity.rudder)
                put("elevator", planeEntity.elevator)
                put("ailerionRight", planeEntity.ailerionRight)
                put("ailerionLeft", planeEntity.ailerionLeft)
            }

            Log.d("sendPlaneData", "Sending data to $url: $jsonData")

            CoroutineScope(Dispatchers.IO).launch {
                val result = postJsonData(url, jsonData.toString())
                withContext(Dispatchers.Main) {
                    if (result) {
                        Log.d("sendPlaneData", "Data sent successfully")
                        lastSentPlaneEntity = planeEntity.copy()
                    } else {
                        Log.e("sendPlaneData", "Failed to send data")
                    }
                }
            }
        } else {
            Log.e("sendPlaneData", "Throttle value is not valid: ${planeEntity.throttle}")
        }
    }

    private suspend fun postJsonData(urlString: String, jsonData: String): Boolean {
        return withContext(Dispatchers.IO) {
            try {
                val url = URL(urlString)
                val connection = url.openConnection() as HttpURLConnection
                connection.requestMethod = "POST"
                connection.setRequestProperty("Content-Type", "application/json; utf-8")
                connection.doOutput = true

                val outputStream: OutputStream = connection.outputStream
                outputStream.write(jsonData.toByteArray())
                outputStream.flush()
                outputStream.close()

                val responseCode = connection.responseCode
                Log.d("postJsonData", "POST Response Code :: $responseCode")

                connection.disconnect()
                responseCode == 200
            } catch (e: Exception) {
                Log.e("postJsonData", "Error during POST request", e)
                false
            }
        }
    }
}


