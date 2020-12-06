import React, {useState, useEffect} from 'react';
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
 * Spotify User Search widget.
 */
const SpotifyUserSearch = () => {
    const [initialized, setInitialized] = useState(false);
    const [connected, setConnected] = useState(false);
    const [failure, setFailure] = useState(false);
    const [authLink, setAuthLink] = useState("/api/spotify/auth");
    const [loading, setLoading] = useState(false);
    const [spotifyUserSearchData, setData] = useState({
      pseudo: "vypslm1ucpqc45839pxq588yl",
      display_name: "",
      followers: ""
    });

    /**
     * Launched in loop.
     */
    useEffect(() => {
        let mounted = false;

        if (!mounted)
        {
          checkConnection();
        }

        var interval = setInterval(() => {
            checkConnection();
        }, 3000);

        return () => {mounted = true, clearInterval(interval)};
    }, []);

    /**
     * Checks for spotify tokens.
     */
    const checkConnection = () => {
      fetch(`/api/spotify/auth`)
        .then(res => {
          if (!res.ok) {
            throw new Error("Channel not found.");
          }
          return res.text();
        })
        .then(res => {
          console.log(res)
          if (res == "null") {
            setConnected(true);
            setData(res => {
              updateSpotify(res.pseudo);
              return res;
            });
          } else {
            setAuthLink(res);
            setInitialized(true);
          }
        })
        .catch(function(error) {
          console.log(error.message)
          setConnected(false);
          setInitialized(true);
        })
    }

    /**
     * Updates the spotify user search UI.
     * @param {*} userName
     */
    const updateSpotify = (userName) => {
      if (userName == null) return;
      if (loading) return;

      setLoading(true);
      fetch(`/api/spotify/data/${userName}`)
      .then(res => {
        if (!res.ok) {
          setFailure(true);
          throw new Error("Spotify account not found.");
        }
        return res.json()
      })
      .then(res => {
        setData(data => {
          return {
            pseudo: res.data.pseudo.toString(),
            display_name: res.data.display_name.toString(),
            followers: res.data.followers.toString()
          }
        });
        setFailure(false);
        setInitialized(true);
        setLoading(false);
      })
      .catch(function(error) {
        console.log(error.message)
        setInitialized(true);
        setFailure(true);
        setLoading(false);
      })
    }

    /**
     * Handles input bar.
     * @param {*} e
     */
    const spotifyUserPress = (e) => {
      if(e.key === "Enter") {
        updateSpotify(e.target.value);
        e.preventDefault();
      }
    }


    return (
      <div>
        {initialized ?
        // Initialized
        <div>
          {!connected ?
            // Disconnected
            <Button href={`${authLink}`} variant="contained" size="large" color="secondary"
            className="connectionButton" startIcon={<LinkIcon />}>
              Connect
            </Button>
            :
            // Connected
            <div>
            <form noValidate>
              <TextField onKeyPress={spotifyUserPress} id="outlined" defaultValue={spotifyUserSearchData.pseudo} label="Username" variant="outlined" />
            </form>
            <br></br>
            {!failure ?
            <div className="paragraph">
              Account : {spotifyUserSearchData.display_name}
              <br></br>
              Followers : {spotifyUserSearchData.followers}
            </div>
            :
            <div className="paragraphCentered">
              Can't find user.
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

export default SpotifyUserSearch;

if (document.getElementById('spotifyUserSearch')) {
    ReactDOM.render(<SpotifyUserSearch />, document.getElementById('spotifyUserSearch'));
}