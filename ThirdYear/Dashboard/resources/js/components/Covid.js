import React, {useState, useEffect} from 'react';
import _ from "lodash";
import "./App.css";
import TextField from '@material-ui/core/TextField';

import IconButton from '@material-ui/core/IconButton';
import FavoriteIcon from '@material-ui/icons/Favorite';

// Mandatory
import ReactDOM from 'react-dom';

/**
 * Covid widget.
 */
const Covid = () => {
    const [initialized, setInitialized] = useState(false);
    const [failure, setFailure] = useState(false);
    const [loading, setLoading] = useState(false);
    const [covidData, setData] = useState({
      code: "",
      nom: "",
      date: "",
      hospitalises: "",
      reanimation: "",
      deces: "",
      gueris: ""
    });
    const [target, setTarget] = useState("Meurthe-et-Moselle");

    /**
     * Launched in loop.
     */
    useEffect(() => {
        let mounted = true;

        if (mounted)
        {
          updateCovid();
        }

        return () => {mounted = true};
    }, []);

    /**
     * Updates covid infos.
     */
    const updateCovid = () => {
      if (loading == true) return;
        console.log(`esh ${target}`)
      setLoading(true);
      fetch(`/api/covid/${target}`)
        .then(res => {
          if (!res.ok) {
            throw new Error("County not found");
          }
          return res.json();
        })
        .then(res => {
          setData(data => {
            return {
                code: res.data.code.toString(),
                nom: res.data.nom.toString(),
                date: res.data.date.toString(),
                hospitalises: res.data.hospitalises.toString(),
                reanimation: res.data.reanimation.toString(),
                deces: res.data.deces.toString(),
                gueris:res.data.gueris.toString()
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
     * Handles the input bar.
     * @param {*} e 
     */
    const handleFirst = (e) => {
        if (e.key === "Enter")
        {
            updateCovid();
            e.preventDefault();
        }
    };

    return (
      <div>
        {initialized ?
        // Initialized
        <div>
          <form noValidate>
            <TextField defaultValue={target} onKeyUp={e => setTarget(e.target.value)} onKeyPress={e => handleFirst(e)} id="outlined" label="Département" variant="outlined" />
          </form>
          <br />
          <br></br>
          {!failure ?
            <div>
              <a>
                <div className="paragraph">
                  Département : {covidData.nom} [{covidData.code}]<br />
                  Date : {covidData.date}<br /><br />

                  Hospitalisés : {covidData.hospitalises}<br />
                  En réanimation : {covidData.reanimation}<br />
                  Décès : {covidData.deces}<br />
                  Guéris : {covidData.gueris}<br />
                </div>
              </a>
            </div>
            :
            <div>
            Département non trouvé ;(
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

export default Covid;

if (document.getElementById('covid')) {
    ReactDOM.render(<Covid />, document.getElementById('covid'));
}