package com.example.epicture

import android.content.Intent
import android.os.Bundle
import com.google.android.material.appbar.CollapsingToolbarLayout
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.google.android.material.snackbar.Snackbar
import androidx.appcompat.app.AppCompatActivity
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.*
import androidx.recyclerview.widget.LinearLayoutManager
import kotlinx.android.synthetic.main.activity_home.*
import kotlinx.android.synthetic.main.activity_user_favorites.*
import kotlinx.android.synthetic.main.activity_user_favorites.rv_recyclerView
import kotlinx.android.synthetic.main.profile_top_toolbar.*
import okhttp3.Call
import okhttp3.Callback
import okhttp3.Response
import org.json.JSONArray
import org.json.JSONObject
import java.io.IOException

class HomeActivity : AppCompatActivity()
{
    /// List of posts data
    private var imgurPosts = mutableListOf<ImgurPost>()
    private lateinit var searchBar: EditText
    private lateinit var loadingDisplay: TextView

    /**
     * onCreate
     * setup gui and call method to get standard posts
     *
     * @param savedInstanceState
     */
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_home)

        setSupportActionBar(findViewById(R.id.toolbar))

        searchBar = findViewById(R.id.searchBar)
        loadingDisplay = findViewById(R.id.loadingDisplay)

        filtersCreation()

        getGalleryStandardPosts()
    }

    /// Actual filters
    var trendingFilter = "viral"
    var timeFilter = "day"

    /// Filters map for equivalent
    var trendingFilterEquivalents: MutableMap<String, String> = mutableMapOf()
    var timeFilterEquivalents: MutableMap<String, String> = mutableMapOf()

    /**
     * filtersCreation
     * Create the filters dropdown and fill maps of filter fake names
     *
     */
    private fun filtersCreation()
    {
        /// Trending filters
        trendingFilterEquivalents["Trending"] = "viral"
        trendingFilterEquivalents["Views"] = "top"
        trendingFilterEquivalents["Recent"] = "time"

        val trendingContent = arrayOf("Trending", "Views", "Recent")

        trendingSpinner.adapter = ArrayAdapter(this, R.layout.custom_spinner, trendingContent)
        trendingSpinner.onItemSelectedListener = object: AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(parent: AdapterView<*>?) {
                TODO("Not yet implemented")
            }
            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                trendingFilter = trendingFilterEquivalents[trendingContent[position]].toString()
                reloadPageWithFilters()
            }
        }

        /// Time filters
        timeFilterEquivalents["Day"] = "day"
        timeFilterEquivalents["Week"] = "week"
        timeFilterEquivalents["Month"] = "month"
        timeFilterEquivalents["Year"] = "year"
        timeFilterEquivalents["All"] = "all"

        val timeContent = arrayOf("Day", "Week", "Month", "Year", "All")

        timeSpinner.adapter = ArrayAdapter(this, R.layout.custom_spinner, timeContent)
        timeSpinner.onItemSelectedListener = object: AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(parent: AdapterView<*>?) {
                TODO("Not yet implemented")
            }
            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                timeFilter = timeFilterEquivalents[timeContent[position]].toString()
                reloadPageWithFilters()
            }
        }
    }

    /**
     * reloadPageWithFilters
     * delete the posts displayed
     * display post (by search or standard) with the new filter
     *
     */
    private fun reloadPageWithFilters()
    {
        clearRecyclerList()

        val searchQuery = getUserSearchTag()
        if (searchQuery.isEmpty() || searchQuery == "null")
        {
            getGalleryStandardPosts()
        }
        else
        {
            getGallerySearchedPosts(searchQuery)
        }
    }

    /**
     * clearRecyclerList
     * remove all the displayed posts & clear the list stocking their data
     *
     */
    private fun clearRecyclerList()
    {
        imgurPosts.clear()

        rv_recyclerView?.adapter?.notifyDataSetChanged()
    }


    /**
     * getGalleryStandardPosts
     * send request to get standard posts with used filters
     *
     */
    private fun getGalleryStandardPosts()
    {
        loadingDisplay.text = "Loading Content ..."
        loadingDisplay.visibility = View.VISIBLE
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
        ImgurApi.getGalleryPosts(callback, "hot", trendingFilter, "0", timeFilter)
    }

    /**
     * getGallerySearchedPosts
     * send a request to search for posts with the searchQuery param and with the filters
     *
     * @param searchQuery
     */
    private fun getGallerySearchedPosts(searchQuery: String)
    {
        loadingDisplay.text = "Loading Content ..."
        loadingDisplay.visibility = View.VISIBLE

        /// Search for everything
        val callback = object : Callback {
            override fun onFailure(call: Call, e: IOException) {}
            override fun onResponse(call: Call, response: Response) {
                if (response.isSuccessful) {
                    if (response.code() in 200..299)
                        apiResponseGestion(response)
                }
            }
        }

        ImgurApi.getSearchGalleryPosts(callback, trendingFilter, timeFilter, "0", searchQuery)
    }

    /**
     * getUserSearchTag
     * simple method that returns what posts the user wants to search (from the textbar)
     *
     * @return
     */
    private fun getUserSearchTag(): String
    {
        return searchBar.text.toString()
    }

    /**
     * searchButtonEffect
     * check if the user has typed a search query
     * clear the displayed posts
     * send request to get posts from research
     *
     * @param view
     */
    fun searchButtonEffect(view: View)
    {
        val searchQuery = getUserSearchTag()
        if (searchQuery.isEmpty() || searchQuery == "null")
        {
            Toast.makeText(applicationContext, "Please fill the search bar", Toast.LENGTH_SHORT).show()
            return
        }

        clearRecyclerList()

        getGallerySearchedPosts(searchQuery)
    }

    /**
     * apiResponseGestion
     * creates ImgurPost from the api data (research or standard posts)
     * display the posts from the data
     *
     * @param response
     */
    private fun apiResponseGestion(response: Response)
    {
        val responseData = response.body()?.string()

        /// Turning the response to a JsonObject
        val json = JSONObject(responseData)
        if (!response.isSuccessful)
        {
            val errors = json.getJSONArray("errors").join(", ")
            throw Exception(errors)
        }

        val jsonArray: JSONArray = json.getJSONArray("data")

        /// Get the data to display an image
        for (i in 0 until jsonArray.length())
        {
            val jsonObj = jsonArray.getJSONObject(i)

            try {
                imgurPosts.add(ImgurPost(jsonObj))
            } catch (e: java.lang.Exception) {

            }
        }

        runOnUiThread {
            rv_recyclerView.layoutManager = LinearLayoutManager(this)
            rv_recyclerView.adapter = RecyclerAdaptater(imgurPosts)
        }
    }

    /**
     * profileButtonEffect
     * redirects to the UserProfileActivity
     *
     * @param menuItem
     */
    fun profileButtonEffect(menuItem: MenuItem)
    {
        val myIntent = Intent(this, UserProfileActivity::class.java)
        startActivity(myIntent)
    }


    /**
     * onCreateOptionsMenu
     * infaltes the menu (GUI)
     *
     * @param menu
     * @return
     */
    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.menu_scrolling, menu)

        return true
    }

    /**
     * onOptionsItemSelected
     * set the action bar item clicks
     *
     * @param item
     * @return
     */
    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.

        return when (item.itemId) {
            R.id.profile_settings -> {
                true
            }
            R.id.action_settings -> {
                /// Action to realize....
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }
}