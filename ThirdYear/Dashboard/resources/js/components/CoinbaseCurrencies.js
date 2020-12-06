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

import stringify from 'uuid/dist/stringify';

import InputLabel from '@material-ui/core/InputLabel';
import MenuItem from '@material-ui/core/MenuItem';
import FormHelperText from '@material-ui/core/FormHelperText';
import FormControl from '@material-ui/core/FormControl';
import Select from '@material-ui/core/Select';

/**
 * Coinbase currencies widget.
 */
const CoinbaseCurrencies = () => {
    const [refreshInterval, setRefreshInterval] = useState(3000);
    const [initialized, setInitialized] = useState(false);
    const [loading, setLoading] = useState(false);
    const [coinbaseData, setData] = useState({
      got: false,
      currency: "BTC",
      value: 0,
      exchangeCurrency: "USD",
      currencyList: ["BTC", "ETC", "LTC", "XRP",
                        "ETC", "DASH", "LINK",
                        "XLM", "EOS", "ATOM"],
      exchangeCurrencyList: ["EUR", "USD"]
    });
    const widget_id = 5;

    /**
     * Launched in loop.
     */
    useEffect(() => {
        let mounted = false;

        if (!mounted)
        {
          updateCoinbase();
        }

        const interval = setInterval(() => {
          updateCoinbase();
        }, 20000);

        return () => {mounted = true, clearInterval(interval)};
    }, []);

    /**
     * Updates currencies informations.
     */
    const updateCoinbase = () => {
      if (loading) return;

      setLoading(true);

      var currency;
      var exchangeCurrency;

      setData(data => {
        currency = data.currency;
        exchangeCurrency = data.exchangeCurrency;
        return data;
      });
      fetch(`/api/coinbase/crypto/${currency}/${exchangeCurrency}`)
      .then(res => {
        if (!res.ok) {
          setData(data => {
            return {
              got: false,
              currency: data.currency,
              exchangeCurrency: data.targeted_currency,
              value: data.targeted_currency_value,
              currencyList: [...data.currencyList],
              exchangeCurrencyList: [...data.exchangeCurrencyList]
            };
          })
          throw new Error("Wallet not found.");
        }
        return res.json()
      })
      .then(res => {
        setData(data => {
          return {
            got: true,
            currency: data.currency,
            exchangeCurrency: res.data.targeted_currency.toString(),
            value: res.data.targeted_currency_value.toString(),
            currencyList: [...data.currencyList],
            exchangeCurrencyList: [...data.exchangeCurrencyList]
          }
        });
        setInitialized(true);
        setLoading(false);
      })
      .catch(function(error) {
        console.log(error.message)
        setInitialized(true);
        setLoading(false);
        setData(data => {
            return {
              got: false,
              currency: data.currency,
              exchangeCurrency: data.exchangeCurrency,
              value: data.value,
              currencyList: [...data.currencyList],
              exchangeCurrencyList: [...data.exchangeCurrencyList]
            }
        })
      })
    }

    /**
     * Slot used to handle select box changes.
     * @param {*} e
     */
    const handleChange = (e) => {
      setData(data => {
        return {
          got: data.got,
          currency: e.target.value,
          exchangeCurrency: data.exchangeCurrency,
          value: data.value,
          currencyList: [...data.currencyList],
          exchangeCurrencyList: [...data.exchangeCurrencyList]
      }});
      updateCoinbase();
    };

    /**
     * Slot used to handle the other select box changes.
     * @param {*} e
     */
    const handleChangeExchange = (e) => {
      coinbaseData.exchangeCurrency = e.target.value;
      setData(data => {
        return {
          got: data.got,
          currency: data.currency,
          exchangeCurrency: e.target.value,
          value: data.value,
          currencyList: [...data.currencyList],
          exchangeCurrencyList: [...data.exchangeCurrencyList]
      }});
      updateCoinbase();
    };


    return (
      <div>
        {initialized ? <div>
          {(coinbaseData.got) ? <div>
            <FormControl variant="outlined">
            <InputLabel id="demo-simple-select-outlined-label">Currency</InputLabel>
            <Select
              labelId="demo-simple-select-outlined-label"
              id="demo-simple-select-outlined"
              value={coinbaseData.currency}
              onChange={handleChange}
              label="Currency"
            >
              {coinbaseData.currencyList.map((el, index) => {
                return (
                  <MenuItem key={index} value={`${el}`}>{el}</MenuItem>
                );
              })}
            </Select>
            </FormControl>&emsp;&emsp;
            <FormControl variant="outlined">
            <InputLabel id="demo-simple-select-outlined-label">Exchange Currency</InputLabel>
            <Select
              labelId="demo-simple-select-outlined-label"
              id="demo-simple-select-outlined"
              value={coinbaseData.exchangeCurrency}
              onChange={handleChangeExchange}
              label="Exchange Currency"
            >
              {coinbaseData.exchangeCurrencyList.map((el, index) => {
                return (
                  <MenuItem key={index} value={`${el}`}>{el}</MenuItem>
                );
              })}
            </Select>
            </FormControl><br /><br />
            {(!loading) ?
            <div className="paragraphCentered">
              {coinbaseData.currency} : {coinbaseData.value} {coinbaseData.exchangeCurrency}
            </div>
            :
            <div className="paragraphCentered">
            Loading...
            </div>
            }
          </div>
          :
          <div>
            Can't get currencies data.
          </div>
          }
        </div>
        :
        <div>
          Initializing...
        </div>
        }
      </div>
    );
}

export default CoinbaseCurrencies;

if (document.getElementById('coinbaseCurrencies')) {
    ReactDOM.render(<CoinbaseCurrencies />, document.getElementById('coinbaseCurrencies'));
}