package com.example.epicture

import android.content.Intent
import android.opengl.Visibility
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.ImageView
import android.widget.LinearLayout
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.squareup.picasso.Picasso
import okhttp3.*
import org.json.JSONObject
import java.io.IOException

class UserProfileActivity : AppCompatActivity()
{
    /**
     * onCreate
     * call the method to display user posts
     *
     * @param savedInstanceState
     */
    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_user_profile)

        findViewById<Button>(R.id.about_button).isClickable = false

        getProfileData()
    }

    /**
     * getProfileData
     * Call two methods
     * One to get user simple information (mail, pseudo...)
     * One to get profile picture
     *
     */
    private fun getProfileData()
    {
        api_getProfilePicture()
        api_getUserData()
    }

    /**
     * api_getProfilePicture
     * send a request to get the user profile picture
     *
     */
    private fun api_getProfilePicture()
    {
        val callback = object : Callback {
            override fun onFailure(call: Call, e: IOException) {}
            override fun onResponse(call: Call, response: Response) {
                if (response.isSuccessful) {
                    if (response.code() in 200..299)
                        setProfilePicture(response)
                }
            }
        }
        ImgurApi.getMyProfilePicture(callback)
    }

    /**
     * setProfilePicture
     * set the profile picture by the data from the api
     *
     * @param response
     */
    private fun setProfilePicture(response: Response)
    {
        val responseData = response.body()?.string()

        /// Turning the response to a JsonObject
        val json = JSONObject(responseData)
        if (!response.isSuccessful)
        {
            val errors = json.getJSONArray("errors").join(", ")
            throw Exception(errors)
        }

        /// Get the profile picture and assign display it
        val link = json.getJSONObject("data")["avatar"].toString()
        val profilePictureImage = findViewById<ImageView>(R.id.profile_picture)
        runOnUiThread {
            Picasso.get()
                .load(link)
                .into(profilePictureImage)
        }
    }

    /**
     * api_getUserData
     * send a request to get some simple data from the user
     *
     */
    private fun api_getUserData()
    {
        val callback = object : Callback {
            override fun onFailure(call: Call, e: IOException) {}
            override fun onResponse(call: Call, response: Response) {
                if (response.isSuccessful) {
                    if (response.code() in 200..299)
                        parseUserData(response)
                }
            }
        }
        ImgurApi.getMyAccountData(callback)
    }

    /**
     * parseUserData
     * display some data from the user in textviews
     *
     * @param response
     */
    private fun parseUserData(response: Response)
    {
        /// Turning the response to a JsonObject
        val responseData = response.body()?.string()
        val json = JSONObject(responseData)

        if (!response.isSuccessful)
        {
            val errors = json.getJSONArray("errors").join(", ")
            throw Exception(errors)
        }

        /// Parsing data, stocking it into a map
        val dataMap: MutableMap<Any, Any> = mutableMapOf()
        val data: JSONObject = json.getJSONObject("data")
        val dataNames = data.names()
        for (i in 0 until data.length()) {
            val dataIndex: String = dataNames[i].toString()
            val dataValue: String = data[dataIndex].toString()
            dataMap[dataIndex] = dataValue
        }

        /// Temporary text fill
        runOnUiThread {
            val accountTmp = "${dataMap["account_url"]}"
            val emailTmp = "${dataMap["email"]}"
            val blockedUsersTmp = "${dataMap["blocked_users"]}"
            findViewById<TextView>(R.id.account_value).text = accountTmp
            findViewById<TextView>(R.id.email_value).text = emailTmp
            findViewById<TextView>(R.id.blocked_users_value).text = blockedUsersTmp
            findViewById<TextView>(R.id.loadingProfileDisplay).visibility = View.GONE
            findViewById<LinearLayout>(R.id.profile_layout).visibility = View.VISIBLE
        }
    }

    /**
     * profile_homeButtonEffect
     * redirects to the home activity
     *
     * @param view
     */
    fun profile_homeButtonEffect(view: android.view.View)
    {
        val myIntent = Intent(this, HomeActivity::class.java)
        startActivity(myIntent)
        finish()
    }

    /**
     * profile_postsButtonEffect
     * redirects to the UserPostsActivity
     *
     * @param view
     */
    fun profile_postsButtonEffect(view: android.view.View)
    {
        val myIntent = Intent(this, UserPostsActivity::class.java)
        startActivity(myIntent)
        finish()
    }

    /**
     * profile_favoritesButtonEffect
     * redirects to the UserFavoritesActivity
     *
     * @param view
     */
    fun profile_favoritesButtonEffect(view: android.view.View)
    {
        val myIntent = Intent(this, UserFavoritesActivity::class.java)
        startActivity(myIntent)
        finish()
    }

    /**
     * profile_aboutButtonEffect
     * redirects to the UserProfileActivity
     *
     * @param view
     */
    fun profile_aboutButtonEffect(view: android.view.View)
    {
        val myIntent = Intent(this, UserProfileActivity::class.java)
        startActivity(myIntent)
        finish()
    }
}