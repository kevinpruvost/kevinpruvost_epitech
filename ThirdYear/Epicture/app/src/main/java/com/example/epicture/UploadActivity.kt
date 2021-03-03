package com.example.epicture

import android.Manifest
import android.app.Activity
import android.app.AlertDialog
import android.content.ActivityNotFoundException
import android.content.DialogInterface
import android.content.Intent
import android.content.pm.PackageManager
import android.database.Cursor
import android.graphics.Bitmap
import android.net.Uri
import android.os.Bundle
import android.provider.MediaStore
import android.provider.Settings
import android.util.Log
import android.view.View
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import okhttp3.Call
import okhttp3.Callback
import okhttp3.Response
import java.io.*
import java.lang.Exception
import java.time.LocalDateTime
import java.util.Base64;

class UploadActivity : AppCompatActivity()
{
    /// The edit texts to get data of the futur post
    private lateinit var titleInputfield: EditText
    private lateinit var descriptionInputfield: EditText

    /// The image in bas64 with the textView displaying its name
    private lateinit var fileTextView: TextView
    private var image: String? = null

    /**
     * onCreate
     * Get the GUI elements to access to their properties later
     *
     * @param savedInstanceState
     */
    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_upload)

        fileTextView = findViewById(R.id.upload_file_uploaded_text)

        titleInputfield = findViewById(R.id.upload_title_inputfield)
        descriptionInputfield = findViewById(R.id.upload_description_inputfield)
    }

    /**
     * upload_validateButtonEffect
     * check if the user has fill a name and a description for the new post
     * if yes, call a method to call the api to upload the new post
     *
     * @param view
     */
    fun upload_validateButtonEffect(view: android.view.View)
    {
        Toast.makeText(applicationContext, "Sending content...", Toast.LENGTH_SHORT).show()
        if (descriptionInputfield.text.isNullOrEmpty() || titleInputfield.text.isNullOrEmpty() || image == null)
        {
            Toast.makeText(applicationContext, "Please fill everything!", Toast.LENGTH_SHORT).show()
            return
        }

        api_sendNewPost()
    }

    /**
     * upload_cancelButtonEffect
     * redirects to the UserPostsActivity
     *
     * @param view
     */
    fun upload_cancelButtonEffect(view: android.view.View)
    {
        val myIntent = Intent(this, UserPostsActivity::class.java)
        startActivity(myIntent)
        finish()
    }

    /**
     * upload_galleryButtonEffect
     * check for permissions by calling askForPermissions()
     * if permissions call openGalleryForImage() to access to gallery
     * @param view
     */
    fun upload_galleryButtonEffect(view: View?)
    {
        if (askForPermissions())
        {
            openGalleryForImage()
        }
    }


    /**
     * encoder
     * converts a image (filepath in string) to base 64
     *
     * @param filePath
     * @return
     */
    fun encoder(fileURI: Uri): String {
        val bytes = contentResolver.openInputStream(fileURI)?.readBytes()
        //val bytes = File(filePath).readBytes()
        return Base64.getEncoder().encodeToString(bytes)
    }

    /**
     * api_sendNewPost
     * start a request to upload a new post with ImgurApi.postNewPicBase64()
     *
     */
    private fun api_sendNewPost()
    {
        val callback = object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                runOnUiThread {
                    Toast.makeText(applicationContext, "Upload exception : ${e.message}", Toast.LENGTH_LONG).show()
                }
            }
            override fun onResponse(call: Call, response: Response) {
                returnToHome()
            }
        }

        ImgurApi.postNewPicBase64(
            callback,
            image.toString(),
            fileTextView.text.toString(),
            titleInputfield.text.toString(),
            descriptionInputfield.text.toString())
    }

    /**
     * returnToHome
     * redirects to UserPostsActivity
     *
     */
    private fun returnToHome()
    {
        runOnUiThread {
            Toast.makeText(applicationContext, "Content successfully sent !", Toast.LENGTH_SHORT).show()
        }
        Thread.sleep(1000)
        val myIntent = Intent(this, UserPostsActivity::class.java)
        startActivity(myIntent)
        finish()
    }

    /**** Take picture ****/
    val REQUEST_IMAGE_CAPTURE = 1

    /**
     * dispatchTakePictureIntent
     * start an intent for result (REQUEST_IMAGE_CAPTURE = 1)
     * the intent make the user take a picture in order to upload it
     *
     * @param view
     */
    fun dispatchTakePictureIntent(view: View) {
        val takePictureIntent = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
        try {
            startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE)
        } catch (e: ActivityNotFoundException) {
            // display error state to the user
        }
    }

    /***** Gallery opening and usage gestion *****/

    val UPLOAD_REQUEST_CODE = 100

    /**
     * openGalleryForImage
     * start an intent for result (REQUEST_IMAGE_CAPTURE = 100)
     * the intent make the user take a picture from his gallery in order to upload it
     *
     */
    private fun openGalleryForImage()
    {
        val intent = Intent(Intent.ACTION_PICK)
        intent.type = "image/*"
        startActivityForResult(intent, UPLOAD_REQUEST_CODE)
    }

    /**
     * onPictureTaken
     * after the user took a picture with his camera, get the data of the picture and stock it
     * generate and display the name of the picture
     *
     * @param data
     */
    private fun onPictureTaken(data: Intent?)
    {
        runOnUiThread {
            val newText = "${LocalDateTime.now()}.jpg"
            fileTextView.text = newText
        }

        /// Get the picture and convert it to base64
        val imageBitmap = data?.extras?.get("data") as Bitmap
        val byteArrayOutputStream = ByteArrayOutputStream()
        imageBitmap.compress(Bitmap.CompressFormat.PNG, 100, byteArrayOutputStream)
        val byteArray: ByteArray = byteArrayOutputStream.toByteArray()

        image = Base64.getEncoder().encodeToString(byteArray)

    }

    /**
     * onPictureChosen
     * after the user took a picture with his camera, get the data of the picture and stock it
     * display the name of the chosen picture
     *
     * @param data
     */
    private fun onPictureChosen(data: Intent?)
    {
        val path = data?.data?.let { getRealPathFromURI(it) }
        /// display the chosen file

        try {
            if (path != null) {
                image = path?.let { data?.data?.let { encoder(it) } }
                runOnUiThread {
                    val newText = path.toString().substring(path.toString().lastIndexOf('/') + 1)
                    fileTextView.text = newText
                }
            }
        } catch (e: Exception) {
            Toast.makeText(applicationContext, "Error : ${e.toString()}", Toast.LENGTH_LONG).show()
        }
    }

    /**
     * onActivityResult
     * check for the result of the intentForResult
     * REQUEST_IMAGE_CAPTURE = 1 for a picture from the camera : call onPictureTaken()
     * UPLOAD_REQUEST_CODE = 100 for a picture from the gallery : call onPictureChosen()
     *
     *
     * @param requestCode
     * @param resultCode
     * @param data
     */
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {
            onPictureTaken(data)
        }

        else if (requestCode == UPLOAD_REQUEST_CODE && resultCode == Activity.RESULT_OK) {
            onPictureChosen(data)
        }
    }

    /**
     * getRealPathFromURI
     * get the real path (in string) for a picture chose in gallery
     *
     * @param contentURI
     * @return
     */
    private fun getRealPathFromURI(contentURI: Uri): String? {
        val cursor: Cursor? = contentResolver.query(contentURI, null, null, null, null)
        return if (cursor == null) {
            contentURI.path
        } else {
            cursor.moveToFirst()
            val idx: Int = cursor.getColumnIndex(MediaStore.Images.ImageColumns.DATA)
            cursor.getString(idx)
        }
    }

    /**
     * isPermissionsAllowed
     * check if the user has access to the gallery
     *
     * @return
     */
    private fun isPermissionsAllowed(): Boolean {
        return ContextCompat.checkSelfPermission(
            this,
            Manifest.permission.READ_EXTERNAL_STORAGE
        ) == PackageManager.PERMISSION_GRANTED
    }

    /**
     * askForPermissions
     * check if the application has permission to access to the gallery
     * if not call a method to ask permission with dialog
     *
     * @return
     */
    private fun askForPermissions(): Boolean {
        if (!isPermissionsAllowed()) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(
                    this as Activity,
                    Manifest.permission.READ_EXTERNAL_STORAGE
                )
            ) {
                showPermissionDeniedDialog()
            } else {
                ActivityCompat.requestPermissions(
                    this as Activity,
                    arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE),
                    +UPLOAD_REQUEST_CODE
                )
            }
            return false
        }
        return true
    }

    /**
     * onRequestPermissionsResult
     * on permission given, ask to open gallery
     *
     * @param requestCode
     * @param permissions
     * @param grantResults
     */
    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String>,
        grantResults: IntArray
    ) {
        when (requestCode) {
            UPLOAD_REQUEST_CODE -> {
                if (grantResults.size > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    openGalleryForImage()
                } else {
                    upload_galleryButtonEffect(null)
                }
                return
            }
        }
    }

    /**
     * showPermissionDeniedDialog
     * dialog that asks for permission to open gallery from the application
     *
     */
    private fun showPermissionDeniedDialog() {
        AlertDialog.Builder(this)
            .setTitle("Permission Denied")
            .setMessage("Permission is denied, Please allow permissions from App Settings.")
            .setPositiveButton("App Settings",
                DialogInterface.OnClickListener { dialogInterface, i ->
                    // send to app settings if permission is denied permanently
                    val intent = Intent()
                    intent.action = Settings.ACTION_APPLICATION_DETAILS_SETTINGS
                    val uri = Uri.fromParts("package", getPackageName(), null)
                    intent.data = uri
                    startActivity(intent)
                })
            .setNegativeButton("Cancel", null)
            .show()
    }
}