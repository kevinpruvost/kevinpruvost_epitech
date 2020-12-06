<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Redirect;

class CalendarController extends Controller
{
    protected $client_id = "566268829747-9lejstu9nvfnv9v9hqtgesq9ks69vags.apps.googleusercontent.com";
    protected $client_secret = "wj_FAQwPYER4zlqdXOPyLEVz";
    protected $redirect_uri = "http://localhost:8080/api/calendar/token";


    protected $scopes = "https://www.googleapis.com/auth/calendar.events.readonly";

    protected $authorization_code = "";
    protected $access_token = "";
    protected $refresh_token = "";


    protected $summary = "";
    protected $htmlLink = "";
    protected $startDate = "";
    protected $endDate = "";

    /// Get Auth Code For Calendar Api
    function getAuthorisationCode() {
        if (DBController::is_access_token(Auth::id(), DBController::get_service_id('Google Calendar')) == false)
            return ('https://accounts.google.com/o/oauth2/v2/auth?client_id='. $this->client_id . '&redirect_uri=' . $this->redirect_uri .'&response_type=code&scope=https://www.googleapis.com/auth/calendar.events.readonly');

        $this->retrieveToken();
        if (!$this->getLastEventInfo())
            return ('https://accounts.google.com/o/oauth2/v2/auth?client_id='. $this->client_id . '&redirect_uri=' . $this->redirect_uri .'&response_type=code&scope=https://www.googleapis.com/auth/calendar.events.readonly');
        return "null";
    }

    /// Retrieve Auth code in Url For Calendar Api
    function getCodeFromUrl() {
        $url = url()->full();
        $parsed = parse_url($url);

        parse_str($parsed['query'], $url_args);

        return $url_args['code'];
    }

    /// Retrieve token from Db For Calendar Api
    function retrieveToken() {
        $this->access_token = DBController::get_access_token(Auth::id(), DBController::get_service_id('Google Calendar'));
        $this->refresh_token = DBController::get_refresh_token(Auth::id(), DBController::get_service_id('Google Calendar'));
    }

    /// Exchange Auth code for access and refresh token For Calendar Api
    function getAccessAndRefreshToken() {
        $response =  Http::asForm()->post('https://oauth2.googleapis.com/token', [
            'grant_type' => 'authorization_code',
            'code' => $this->authorization_code,
            'redirect_uri' => $this->redirect_uri,
            'client_id' => $this->client_id,
            'client_secret' => $this->client_secret,
        ]);

        //$response = $response->json();
        log::debug("response = " . $response);
        $this->access_token = $response['access_token'];
        //$this->refresh_token = $response['refresh_token'];

        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Google Calendar'), $this->access_token, '0');
        redirect::to("/dashboard");
    }

    /// Refresh access token For Calendar Api
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


    /// Call an endpoint in Calendar Api to get the next event for a user For Calendar Api
    function getLastEventInfo() {
        $api = Http::withToken($this->access_token)->get('https://www.googleapis.com/calendar/v3/calendars/primary/events');

        $api = $api->json();

        if (array_key_exists('error', $api))
            return false;

        $this->summary = $api['items'][count($api['items']) - 1]['summary'];
        $this->htmlLink = $api['items'][count($api['items']) - 1]['htmlLink'];
        $this->startDate = substr($api['items'][count($api['items']) - 1]['start']['dateTime'], 0, 10) . " " . substr($api['items'][count($api['items']) - 1]['start']['dateTime'], 11, 8);
        $this->endDate = substr($api['items'][count($api['items']) - 1]['end']['dateTime'], 0, 10) . " " . substr($api['items'][count($api['items']) - 1]['end']['dateTime'], 11, 8);
        return true;
    }

    /// link functions to get access and refresh tokens For Calendar Api
    function generateAccessAndRefreshToken() {
        ///retrieve tokens
        $this->authorization_code = $this->getCodeFromUrl();
        $this->getAccessAndRefreshToken();

        return redirect::to("/");
    }

    /// route Endpoint to retrieve data  For Calendar Api
    function getData() {
        $this->retrieveToken();
        $this->getLasteventInfo();

        $js = array(
            "summary" => $this->summary,
            "startDate" => $this->startDate,
            "endDate" => $this->endDate,
            "htmlLink" => $this->htmlLink
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


        /// return la vue
    }
}
