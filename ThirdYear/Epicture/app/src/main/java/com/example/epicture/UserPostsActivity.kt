package com.example.epicture

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import kotlinx.android.synthetic.main.activity_user_posts.*
import okhttp3.*
import org.json.JSONArray
import org.json.JSONObject
import java.io.IOException

class UserPostsActivity : AppCompatActivity() {

    // List of ImgurPost objects to create posts
    private var imgurPosts = mutableListOf<ImgurPost>()
    private lateinit var loadingDisplay: TextView

    /**
     * onCreate
     * send a request to get the user posts
     *
     * @param savedInstanceState
     */
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_user_posts)

        findViewById<Button>(R.id.posts_button).isClickable = false

        loadingDisplay = findViewById(R.id.loadingDisplayPosts)

        val callback = object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                runOnUiThread {
                    loadingDisplay.text = "Failed to load gallery images"
                    loadingDisplay.visibility = View.VISIBLE
                }
            }
            override fun onResponse(call: Call, response: Response) {
                if (response.isSuccessful) {
                    if (response.code() in 200..299)
                        apiResponseGestion(response)
                    runOnUiThread {
                        loadingDisplay.visibility = View.GONE
                    }
                }
            }
        }

        ImgurApi.getMyPosts(callback)
    }


    /**
     * apiResponseGestion
     * parse the data from the user posts api request & display the user posts
     *
     * @param response
     */
    private fun apiResponseGestion(response: Response) {
        val responseData = response.body()?.string()

        /// Turning the response to a JsonObject
        val json = JSONObject(responseData)
        if (!response.isSuccessful) {
            val errors = json.getJSONArray("errors").join(", ")
            throw Exception(errors)
        }

        val jsonArray: JSONArray = json.getJSONArray("data")

        /// Get the data to display an image
        for (i in 0 until jsonArray.length()) {
            val jsonObj = jsonArray.getJSONObject(i)
            imgurPosts.add(ImgurPost(jsonObj))
        }
        runOnUiThread {
            rv_recyclerView.layoutManager = LinearLayoutManager(this)
            rv_recyclerView.adapter = RecyclerAdaptater(imgurPosts)
        }
    }


    /**
     * profile_uploadButtonEffect
     * redirects to the UploadActivity
     *
     * @param view
     */
    fun profile_uploadButtonEffect(view: android.view.View) {
        val myIntent = Intent(this, UploadActivity::class.java)
        startActivity(myIntent)
        finish()
    }

    /**
     * profile_homeButtonEffect
     * redirects to the HomeActivity
     *
     * @param view
     */
    fun profile_homeButtonEffect(view: android.view.View) {
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
    fun profile_postsButtonEffect(view: android.view.View) {
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
    fun profile_favoritesButtonEffect(view: android.view.View) {
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
    fun profile_aboutButtonEffect(view: android.view.View) {
        val myIntent = Intent(this, UserProfileActivity::class.java)
        startActivity(myIntent)
        finish()
    }
}