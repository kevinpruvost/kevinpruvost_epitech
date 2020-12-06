<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;

class WeatherController extends Controller
{
    public $report = "";

    public function setReport($inputreport) {

        $this->report = $inputreport;

    }

    public function getReport() {

        return $this->report;

    }

    /// route Endpoint to retrieve data  For Weather Api
    function create($town = "nancy")
    {
        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Weather'), '0', '0');
        $api = 'https://prevision-meteo.ch/services/json/' . $town;

        $response = Http::get($api);

        $report = $response->json();

        $js = array(
            "city_name" => $report['city_info']['name'],
            "icon" => $report['current_condition']['icon'],
            "condition" => $report['current_condition']['condition'],
            "tmp" => $report['current_condition']['tmp'],
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }

    public function render()
    {
        return view('components.twitter-component');
    }
}
