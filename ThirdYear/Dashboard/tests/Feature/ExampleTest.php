<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Tests\TestCase;
use App\Http\Controllers\CovidController;

class ExampleTest extends TestCase
{
    public function CovidTest()
    {
        $covid = new CovidController;

        return $covid->create("Meurthe-et-Moselle");
    }

    /**
     * A basic test example.
     *
     * @return void
     */
    public function testBasicTest()
    {
        $response = $this->get('/dashboard');

        $response->assertStatus(302);
        $oeuf = $this->CovidTest();
    }
}
