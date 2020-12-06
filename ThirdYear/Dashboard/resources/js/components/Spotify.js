import React, {useState, useEffect} from 'react';
import _ from "lodash";
import {v4} from "uuid";

import Button from '@material-ui/core/Button';

// Mandatory
import ReactDOM from 'react-dom';

import LinkIcon from '@material-ui/icons/Link';

/**
 * Spotify Widget.
 */
const Spotify = () => {
    const [initialized, setInitialized] = useState(false);
    const [connected, setConnected] = useState(false);
    const [failure, setFailure] = useState(false);
    const [authLink, setAuthLink] = useState("/api/spotify/auth");
    const [spotifyData, setData] = useState({
      pseudo: "",
      user_picture: "",
      artist: "",
      album: "",
      song: "",
      cover: ""
    });

    /**
     * Launched in loop.
     */
    useEffect(() => {
        let mounted = true;

        if (mounted)
        {
          checkConnection();
        }

        const interval = setInterval(() => {
          checkConnection();
        }, 10000);

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
            updateSpotify();
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
     * Updates the Spotify interface.
     */
    const updateSpotify = () => {
      fetch(`/api/spotify/data`)
      .then(res => {
        if (!res.ok) {
          setFailure(true);
          throw new Error("Wallet not found.");
        }
        return res.json()
      })
      .then(res => {
        setData(data => {
          return {
            pseudo: res.data.pseudo.toString(),
            user_picture: res.data.user_picture,
            artist: res.data.artist,
            album: res.data.album,
            song: res.data.song,
            cover: res.data.cover
          }
        });
        setFailure(false);
        setInitialized(true);
      })
      .catch(function(error) {
        console.log(error.message)
        setInitialized(true);
        setFailure(true);
      })
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
            {!failure ?
            <div className="paragraph">
              {spotifyData.user_picture != null &&
                <span className={`large_icon`} style={{background: 'url(' + spotifyData.user_picture + ') no-repeat'}}></span>
              }
              Account : {spotifyData.pseudo}
              <br></br>
              {spotifyData.song != "" ?
                <div>
                Playing {spotifyData.artist} - {spotifyData.song}...<br />
                Album : {spotifyData.album}
                { spotifyData.cover != null &&
                    <span className={`large_icon`} style={{background: 'url(' + spotifyData.cover + ') no-repeat'}}></span>
                }
                </div>
                :
                <div>
                No song playing.
                </div>
              }
            </div>
            :
            <div className="paragraphCentered">
              Cannot load your account :(
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

export default Spotify;

if (document.getElementById('spotify')) {
    ReactDOM.render(<Spotify />, document.getElementById('spotify'));
}