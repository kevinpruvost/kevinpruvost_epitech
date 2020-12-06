import React, {useState, useEffect} from 'react';
import _ from "lodash";
import "./App.css";

import LinkIcon from '@material-ui/icons/Link';
import PlayForWorkIcon from '@material-ui/icons/PlayForWork';
import IconButton from '@material-ui/core/IconButton';
import Button from '@material-ui/core/Button';

import { green } from '@material-ui/core/colors';
import { purple } from '@material-ui/core/colors';

// Mandatory
import ReactDOM from 'react-dom';

/**
 * Calendar widget.
 */
const Calendar = () => {
    const [initialized, setInitialized] = useState(false);
    const [connected, setConnected] = useState(false);
    const [failure, setFailure] = useState(false);
    const [authLink, setAuthLink] = useState("/api/calendar/auth");
    const [calendarData, setData] = useState({
      summary: "",
      startDate: "",
      endDate: "",
      htmlLink: ""
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
     * Check if Google Calendar tokens were obtained or not.
     */
    const checkConnection = () => {
      fetch(`/api/calendar/auth`)
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
            updateCalendar();
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
     * Updates the Calendar UI.
     */
    const updateCalendar = () => {

      console.log("updating")
      fetch(`/api/calendar/data`)
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
            summary: res.data.summary.toString(),
            startDate: res.data.startDate.toString(),
            endDate: res.data.endDate.toString(),
            htmlLink: res.data.htmlLink.toString(),
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
              <div className="paragraphCentered">
              Incoming event :
              </div>
              <br />
              Summary : {calendarData.summary}
              <br></br>
              Start : {calendarData.startDate}<br />
              End : {calendarData.endDate}<br /><br />
              <div className="paragraphCentered">
                <IconButton aria-label="sendLove" href={calendarData.htmlLink} target="_blank">
                  <PlayForWorkIcon style={{ fontSize: 50, color: purple[600] }} />
                </IconButton>
              </div>
            </div>
            :
            <div className="paragraphCentered">
              Cannot load events :(
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

export default Calendar;

if (document.getElementById('calendar')) {
    ReactDOM.render(<Calendar />, document.getElementById('calendar'));
}