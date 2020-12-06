<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class AddCalendarWidget extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        DB::table('widgets')->insert(
            array(
                'id' => '9',
                'name' => 'Calendar',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '10',
                'name' => 'Covid',
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
