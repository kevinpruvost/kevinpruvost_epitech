import React, {useState, useEffect} from 'react';
import _ from "lodash";
import "./App.css";
import Button from '@material-ui/core/Button';

import LinkIcon from '@material-ui/icons/Link';
import TextareaAutosize from '@material-ui/core/TextareaAutosize';

// Mandatory
import ReactDOM from 'react-dom';

/**
 * Gmail widget.
 */
const Gmail = () => {
    const [initialized, setInitialized] = useState(false);
    const [connected, setConnected] = useState(false);
    const [failure, setFailure] = useState(false);
    const [authLink, setAuthLink] = useState("/api/gmail/auth");
    const [gmailData, setData] = useState({
      snippet: "",
      from: "",
      date: "",
      subject: ""
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
        }, 5000);

        return () => {mounted = true, clearInterval(interval)};
    }, []);

    /**
     * Checks Gmail tokens.
     */
    const checkConnection = () => {
      fetch(`/api/gmail/auth`)
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
            updateGmail();
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
     * Updates GMail UI.
     */
    const updateGmail = () => {

      console.log("updating")
      fetch(`/api/gmail/data`)
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
            snippet: res.data.snippet.toString(),
            date: res.data.date.toString(),
            from: res.data.from.toString(),
            subject: res.data.subject.toString()
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
              Last mail :
              <br /><br />
              <TextareaAutosize readOnly
                className="textAreaMinSize"
                rowsMax={10}
                aria-label="maximum height"
                value={
                  `Date : ${gmailData.date}\nFrom : ${gmailData.from}\n\nSubject : ${gmailData.subject}\n\nDescription : ${gmailData.snippet}`}
              />
            </div>
            :
            <div className="paragraphCentered">
              Cannot load last mail :(
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

export default Gmail;

if (document.getElementById('gmail')) {
    ReactDOM.render(<Gmail />, document.getElementById('gmail'));
}