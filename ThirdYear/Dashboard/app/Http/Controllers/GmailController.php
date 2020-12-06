<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Redirect;

class GmailController extends Controller
{
    protected $client_id = "566268829747-qcsjl9oapdiedeklaqghivldbsbn4u43.apps.googleusercontent.com";
    protected $client_secret = "-J55XS1YPH2bNgJlOsO7Ia9e";
    protected $redirect_uri = "http://localhost:8080/api/gmail/token";


    protected $scopes = "https://mail.google.com/";

    protected $authorization_code = "";
    protected $access_token = "";
    protected $refresh_token = "";


    protected $last_id = "";
    protected $snippet = "";
    protected $date = "";
    protected $from = "";
    protected $subject = "";


    /// Get Auth Code For Gmail Api
    function getAuthorisationCode() {
        if (DBController::is_access_token(Auth::id(), DBController::get_service_id('Gmail')) == false)
            return ('https://accounts.google.com/o/oauth2/v2/auth?client_id='. $this->client_id . '&redirect_uri=' . $this->redirect_uri .'&response_type=code&scope=https://mail.google.com/&prompt=consent&include_granted_scopes=true');

        $this->retrieveToken();
        if (!$this->getLastMailId())
            return ('https://accounts.google.com/o/oauth2/v2/auth?client_id='. $this->client_id . '&redirect_uri=' . $this->redirect_uri .'&response_type=code&scope=https://mail.google.com/&prompt=consent&include_granted_scopes=true');
        return "null";
    }

    /// Retrieve Auth code in Url For Gmail Api
    function getCodeFromUrl() {
        $url = url()->full();
        $parsed = parse_url($url);

        parse_str($parsed['query'], $url_args);

        return $url_args['code'];
    }

    /// Retrieve token from Db For Gmail Api
    function retrieveToken() {
        $this->access_token = DBController::get_access_token(Auth::id(), DBController::get_service_id('Gmail'));
        $this->refresh_token = DBController::get_refresh_token(Auth::id(), DBController::get_service_id('Gmail'));
    }

    /// Exchange Auth code for access and refresh token For Gmail Api
    function getAccessAndRefreshToken() {
        $response =  Http::asForm()->post('https://oauth2.googleapis.com/token', [
            'grant_type' => 'authorization_code',
            'code' => $this->authorization_code,
            'redirect_uri' => $this->redirect_uri,
            'client_id' => $this->client_id,
            'client_secret' => $this->client_secret,
        ]);

        //$response = $response->json();

        $this->access_token = $response['access_token'];
        //$this->refresh_token = $response['refresh_token'];

        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Gmail'), $this->access_token, '0');
        redirect::to("/dashboard");
    }

    /// Refresh access token For Gmail Api
    function refreshAccessToken() {
        $response =  Http::post('https://oauth2.googleapis.com/token', [
            'grant_type' => 'refresh_token',
            'refresh_token' => $this->refresh_token,
            'client_id' => $this->client_id,
            'client_secret' => $this->client_secret,
        ]);

        $response = $response->json();

        $this->access_token = $response['access_token'];
    }

    /// Call an endpoint in Gmail Api to get the last mail data for a user For Gmail Api
    function getLastMailId() {
        $api = Http::withToken($this->access_token)->get('https://gmail.googleapis.com/gmail/v1/users/me/messages?maxResults=1');

        $api = $api->json();

        log::debug($api);
        if (!array_key_exists('messages', $api))
            return false;

        $this->last_id = $api['messages'][0]['id'];
        return true;
    }

    /// Call an endpoint in Gmail Api to get the last mail data for a user For Gmail Api
    function getLastMailInfo() {
        $api = Http::withToken($this->access_token)->get('https://gmail.googleapis.com/gmail/v1/users/me/messages/' . $this->last_id);

        $api = $api->json();

        log::debug($api);

        $this->snippet = $api['snippet'];
        $this->from = "No Identity";
        $this->date = "No date";
        $this->subject = "No subject";

        foreach ($api['payload']['headers'] as $header)
        {
            if ($header['name'] == "From")
                $this->from = $header['value'];
            else if ($header['name'] == "Date")
                $this->date = $header['value'];
            else if ($header['name'] == "Subject")
                $this->subject = $header['value'];
        }
    }

    /// link functions to get access and refresh tokens For Gmail Api
    function generateAccessAndRefreshToken() {
        ///retrieve tokens
        $this->authorization_code = $this->getCodeFromUrl();
        $this->getAccessAndRefreshToken();

        return redirect::to("/");
    }

    /// route Endpoint to retrieve data  For Gmail Api
    function getData() {
        $this->retrieveToken();
        $this->getLastMailId();
        $this->getLastMailInfo();

        $js = array(
            "snippet" => $this->snippet,
            "date" => $this->date,
            "from" => $this->from,
            "subject" => $this->subject
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }

    ///depreciated
    function getTokenAndData() {
        ///retrieve tokens
        $this->authorization_code = $this->getCodeFromUrl();
        $this->getAccessAndRefreshToken();

        ///retrieve data
        $this->getLastMailId();
        $this->getLastMailInfo();

        /// return la vue
    }
}
