<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Schema;

class ModifyWidgetTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {

        DB::table('widgets')->truncate();


        DB::table('widgets')->insert(
            array(
                'id' => '1',
                'name' => 'Spotify',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '2',
                'name' => 'Gmail',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '3',
                'name' => 'Weather',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '4',
                'name' => 'Youtube',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '5',
                'name' => 'Coinbase',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '6',
                'name' => 'Coinbase Currencies',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '7',
                'name' => 'Spotify User Search',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '8',
                'name' => 'Love Meter',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '9',
                'name' => 'Google Calendar',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '10',
                'name' => 'Covid Infos',
                'key' => '0'
            )
        );
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        //
    }
}
