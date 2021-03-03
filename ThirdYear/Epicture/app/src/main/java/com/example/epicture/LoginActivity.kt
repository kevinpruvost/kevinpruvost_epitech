package com.example.epicture

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.util.Log
import android.view.animation.Animation
import android.view.animation.AnimationUtils
import android.widget.ImageButton
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity

class LoginActivity : AppCompatActivity()
{
    /**
     * onCreate
     * set up deep linking of login button
     *
     * @param savedInstanceState
     */
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

        /// Redirect to the login platform of the imgur api
        findViewById<ImageButton>(R.id.connexion_button).setOnClickListener{
            linkOpen("https://api.imgur.com/oauth2/authorize?client_id=79fb2772adbae4a&response_type=token")
        }

        var titleImg = findViewById<ImageView>(R.id.titleImageView);
        titleImg.setOnClickListener{
            var animFadeOut = AnimationUtils.loadAnimation(applicationContext, R.anim.fade_out);
            var animFadeIn = AnimationUtils.loadAnimation(applicationContext, R.anim.fade_in);
            animFadeOut.setAnimationListener(object : Animation.AnimationListener {
                override fun onAnimationStart(arg0: Animation) {}
                override fun onAnimationRepeat(arg0: Animation) {}
                override fun onAnimationEnd(arg0: Animation) {
                    titleImg.startAnimation(animFadeIn);
                }
            })
            titleImg.startAnimation(animFadeOut);
        }

        /// Get the data from the deep link
        val urisAction: String? = intent?.action
        val urisData: Uri? = intent?.data
        if (urisAction == "android.intent.action.VIEW" && urisData != null) {
            parseLinkData(urisData.toString())
        }
    }

    /**
     * parseLinkData
     * get data from logging in by deep linking
     * fill the data to the ImgurApi class
     * intent to the HomeActivity
     *
     * @param uri
     */
    private fun parseLinkData(uri: String) {

        /// Parsing the data we got by the api link
        var regex = Regex("(?<=#access_token=)(.*?&)")
        val accessToken = regex.find(input = uri, startIndex = 0)?.value?.dropLast(1)
        regex = Regex("(?<=&expires_in=)(.*?&)")
        val expiresIn = regex.find(input = uri, startIndex = 0)?.value?.dropLast(1)
        regex = Regex("(?<=&token_type=)(.*?&)")
        val tokenType = regex.find(input = uri, startIndex = 0)?.value?.dropLast(1)
        regex = Regex("(?<=&refresh_token=)(.*?&)")
        val refreshToken = regex.find(input = uri, startIndex = 0)?.value?.dropLast(1)
        regex = Regex("(?<=&account_username=)(.*?&)")
        val accountUsername = regex.find(input = uri, startIndex = 0)?.value?.dropLast(1)
        regex = Regex("(?<=&account_id=)(.*)")
        val accountId = regex.find(input = uri, startIndex = 0)?.value

        ImgurApi.accessToken = accessToken
        ImgurApi.expiresIn = expiresIn
        ImgurApi.tokenType = tokenType
        ImgurApi.refreshToken = refreshToken
        ImgurApi.accountUsername = accountUsername
        ImgurApi.accountId = accountId

        /// Moving to the next activity while sending the parsed data
        val myIntent = Intent(this, HomeActivity::class.java)
        myIntent.putExtra("access_token", accessToken)
        myIntent.putExtra("expires_in", expiresIn)
        myIntent.putExtra("token_type", tokenType)
        myIntent.putExtra("refresh_token", refreshToken)
        myIntent.putExtra("account_username", accountUsername)
        myIntent.putExtra("account_id", accountId)
        myIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP)
        myIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK)
        startActivity(myIntent)
    }

    /**
     * linkOpen
     * deep linking intent to login the user to the platform api
     *
     * @param urls
     */
    private fun linkOpen(urls: String) {
        val uris = Uri.parse(urls)
        val intents = Intent(Intent.ACTION_VIEW, uris)
        Log.d("LINK", "Starting intent");
        startActivity(intents)
    }
}