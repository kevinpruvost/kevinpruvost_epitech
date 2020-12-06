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
 * Coinbase Widget.
 */
const Coinbase = () => {
    const [initialized, setInitialized] = useState(false);
    const [connected, setConnected] = useState(false);
    const [failure, setFailure] = useState(false);
    const [authLink, setAuthLink] = useState("/api/coinbase/auth");
    const [coinbaseData, setData] = useState({
      pseudo: "",
      currency: "",
      amount: ""
    });
    const widget_id = 5;

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
     * Checks if the tokens were obtained or not.
     */
    const checkConnection = () => {
      fetch(`/api/coinbase/auth`)
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
            updateCoinbase();
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
     * Updates the coinbase UI.
     */
    const updateCoinbase = () => {

      console.log("updating")
      fetch(`/api/coinbase/data`)
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
            currency: res.data.currency.toString(),
            amount: res.data.amount.toString()
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
              Account : {coinbaseData.pseudo}
              <br></br>
              {coinbaseData.amount} {coinbaseData.currency}
            </div>
            :
            <div className="paragraphCentered">
              Cannot load wallet :(
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

export default Coinbase;

if (document.getElementById('coinbase')) {
    ReactDOM.render(<Coinbase />, document.getElementById('coinbase'));
}