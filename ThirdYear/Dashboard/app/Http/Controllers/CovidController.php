<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;

class CovidController extends Controller
{
    /// route Endpoint to retrieve data  For Covid Api
    function create($departement)
    {
        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Covid Infos'), '0', '0');
        $api = 'https://coronavirusapi-france.now.sh/LiveDataByDepartement?Departement=' . $departement;

        $response = Http::get($api);

        $report = $response->json();

        $js = array(
            "code" => $report['LiveDataByDepartement'][0]['code'],
            "nom" => $report['LiveDataByDepartement'][0]['nom'],
            "date" => $report['LiveDataByDepartement'][0]['date'],
            "hospitalises" => $report['LiveDataByDepartement'][0]['hospitalises'],
            "reanimation" => $report['LiveDataByDepartement'][0]['reanimation'],
            "deces" => $report['LiveDataByDepartement'][0]['deces'],
            "gueris" => $report['LiveDataByDepartement'][0]['gueris']
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }

}
