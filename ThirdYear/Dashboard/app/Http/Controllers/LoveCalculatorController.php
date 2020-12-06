<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;

class LoveCalculatorController extends Controller
{
    protected $apiKey = "34db6126efmshae5aed2d61d6fe4p1deb6fjsn55e113c144a1";

    /// route Endpoint to retrieve data  For Love_calculator Api
    function create($firstName, $secondName)
    {
        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Love Meter'), '0', '0');
        $api = 'https://love-calculator.p.rapidapi.com/getPercentage?fname=' . $firstName . '&sname=' . $secondName;

        $response = Http::withHeaders(['x-rapidapi-key' => $this->apiKey])->get($api);

        $report = $response->json();

        $js = array(
            "fname" => $report['fname'],
            "sname" => $report['sname'],
            "percentage" => $report['percentage'],
            "result" => $report['result'],
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }

}
