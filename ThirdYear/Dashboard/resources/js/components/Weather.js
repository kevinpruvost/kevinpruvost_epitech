import React, {useState, useEffect, memo} from 'react';
import {DragDropContext, Droppable, Draggable} from "react-beautiful-dnd";
import _ from "lodash";
import {v4} from "uuid";
import "./App.css";
import TextField from '@material-ui/core/TextField';
import FormControlLabel from '@material-ui/core/FormControlLabel';

import DeleteIcon from '@material-ui/icons/Delete';
import IconButton from '@material-ui/core/IconButton';
import Button from '@material-ui/core/Button';

// Mandatory
import ReactDOM from 'react-dom';
import { Redirect } from "react-router-dom";

import LinkIcon from '@material-ui/icons/Link';
import SentimentVeryDissatisfiedIcon from '@material-ui/icons/SentimentVeryDissatisfied';
import stringify from 'uuid/dist/stringify';

/**
 * Weather widget.
 */
const Weather = () => {
    const [initialized, setInitialized] = useState(false);
    const [failure, setFailure] = useState(false);
    const [loading, setLoading] = useState(false);
    const [weatherData, setData] = useState({
      city_name: "",
      tmp: "",
      condition: "",
      icon: ""
    });

    /**
     * Launched in loop.
     */
    useEffect(() => {
        let mounted = true;

        if (mounted)
        {
          updateWeather("Nancy");
        }

        var interval = setInterval(() => {
          setData(data => {
            updateWeather(data.city_name);
            return data;
          });
        }, 10000);

        return () => {mounted = true, clearInterval(interval)};
    }, []);

    /**
     * Handles input bar.
     * @param {*} e
     */
    const weatherKeyPress = (e) => {
      if(e.key === "Enter") {
        updateWeather(e.target.value);
        e.preventDefault();
      }
    }

    /**
     * Updates the weather API.
     * @param {*} cityName
     */
    const updateWeather = (cityName) => {
      if (loading == true) return;
      setLoading(true);

      var ress;
      fetch(`/api/weather/${cityName}`)
        .then(res => {
          if (!res.ok) {
            throw new Error("City not found.");
          }
          return res.json();
        })
        .then(res => {
          ress = res;
          setData(data => {
            return {
                city_name: res.data.city_name,
                tmp: res.data.tmp,
                condition: res.data.condition,
                icon: res.data.icon
            };
          });
          setFailure(false);
          setInitialized(true);
          setLoading(false);
        })
        .catch(function(error) {
          console.log(ress)
          console.log(error.message)
          setFailure(true);
          setInitialized(true);
          setLoading(false);
        })
    }

    return (
      <div>
        {initialized ?
        // Initialized
        <div>
          <form noValidate>
                  <TextField onKeyPress={weatherKeyPress} id="outlined" defaultValue={weatherData.city_name} label="Ville" variant="outlined" />
          </form>
          <br></br>
          {loading ?
            <div>
            Loading...
            </div>
            :
            <div>
              {!failure || weatherData.city_name == null ?
              <div>
                  <a>
                  <div className="paragraph">
                    Ville : {weatherData.city_name}<br></br>
                    Température : {weatherData.tmp} degrés<br></br>
                    Condition   : {weatherData.condition}<br></br>
                  </div>
                  <br></br>
                  <span className={`back_icon`} style={{background: 'url(' + weatherData.icon + ') no-repeat'}}></span>
                </a>
              </div>
              :
              <div>
              City weather not found.
              </div>
              }
            </div>
          }
        </div> :
        // Not initialized
        <div>
        Initializing...
        </div>
        }
      </div>
    );
}

export default Weather;

if (document.getElementById('weather')) {
    ReactDOM.render(<Weather />, document.getElementById('weather'));
}