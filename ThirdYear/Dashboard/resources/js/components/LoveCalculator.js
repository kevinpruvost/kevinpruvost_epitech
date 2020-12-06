import React, {useState, useEffect} from 'react';
import _ from "lodash";
import "./App.css";
import TextField from '@material-ui/core/TextField';

import IconButton from '@material-ui/core/IconButton';
import FavoriteIcon from '@material-ui/icons/Favorite';

import { red } from '@material-ui/core/colors';

// Mandatory
import ReactDOM from 'react-dom';

/**
 * Love Meter widget.
 */
const LoveCalculator = () => {
    const [initialized, setInitialized] = useState(false);
    const [failure, setFailure] = useState(false);
    const [loading, setLoading] = useState(false);
    const [loveCalculatorData, setData] = useState({
      fname: "",
      sname: "",
      percentage: "",
      result: ""
    });
    const [firstTarget, setFirstTarget] = useState("Kekou");
    const [secondTarget, setSecondTarget] = useState("Forian");

    /**
     * Launched in loop.
     */
    useEffect(() => {
        let mounted = true;

        if (mounted)
        {
          updateLoveCalculator();
        }

        return () => {mounted = true};
    }, []);

    /**
     * Updates Love Meter.
     */
    const updateLoveCalculator = () => {
      if (loading == true) return;
        console.log(`esh ${firstTarget} ${secondTarget}`)
      setLoading(true);
      fetch(`/api/love/${firstTarget}/${secondTarget}`)
        .then(res => {
          if (!res.ok) {
            throw new Error("Love value not found </3");
          }
          return res.json();
        })
        .then(res => {
          setData(data => {
            return {
                fname: res.data.fname.toString(),
                sname: res.data.sname.toString(),
                percentage: res.data.percentage.toString(),
                result: res.data.result.toString()
            };
          });
          setFailure(false);
          setInitialized(true);
          setLoading(false);
        })
        .catch(function(error) {
          console.log(error.message)
          setFailure(true);
          setInitialized(true);
          setLoading(false);
        })
    }

    /**
     * Handles first input bar.
     * @param {*} e
     */
    const handleFirst = (e) => {
        if (e.key === "Enter")
        {
            updateLoveCalculator();
            e.preventDefault();
        }
    };

    /**
     * Handles second input bar.
     * @param {*} e
     */
    const handleSecond = (e) => {
        if (e.key === "Enter")
        {
            updateLoveCalculator();
            e.preventDefault();
        }
    };

    return (
      <div>
        {initialized ?
        // Initialized
        <div>
          <form noValidate>
            <TextField defaultValue={firstTarget} onKeyUp={e => setFirstTarget(e.target.value)} onKeyPress={e => handleFirst(e)} id="outlined" label="First lover" variant="outlined" />
          </form>
          <br />
          <form noValidate>
            <TextField defaultValue={secondTarget} onKeyUp={e => setSecondTarget(e.target.value)} onKeyPress={e => handleSecond(e)} id="outlined" label="Second lover" variant="outlined" />
          </form>
          <br />
          <div>
            <IconButton aria-label="sendLove" onClick={e => updateLoveCalculator()}>
              <FavoriteIcon style={{ color:red[500] }} fontSize="large" />
            </IconButton>
          </div>
          <br></br>
          {!failure ?
            <div>
              <a>
                <div className="paragraphCentered">
                  Between {loveCalculatorData.fname} and {loveCalculatorData.sname}<br /><br />
                  Love : {loveCalculatorData.percentage}%<br />
                  {loveCalculatorData.result}
                </div>
              </a>
            </div>
            :
            <div>
            Love value not found ;(
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

export default LoveCalculator;

if (document.getElementById('loveCalculator')) {
    ReactDOM.render(<LoveCalculator />, document.getElementById('loveCalculator'));
}