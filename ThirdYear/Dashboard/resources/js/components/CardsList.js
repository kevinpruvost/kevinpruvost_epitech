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

import Coinbase from './Coinbase.js';
import CoinbaseCurrencies from './CoinbaseCurrencies.js';
import Youtube from './Youtube.js';
import Weather from './Weather.js';
import Spotify from './Spotify.js';
import SpotifyUserSearch from './SpotifyUserSearch.js';
import Gmail from './Gmail.js';
import LoveCalculator from './LoveCalculator.js';
import Covid from './Covid.js';
import Calendar from './Calendar.js';

/**
 * Contains the widgets list.
 */
function CardsList() {

  const [text, setText] = useState("")
  const [update, setUpdated] = useState(false)
  const [mounted, setMounted] = useState(false)
  const [state, setState] = useState({
    widgets: {
      title: "",
      items: [],
    }
  })

  let widgetsIds = {
    "Spotify": 1,
    "Gmail": 2,
    "Weather": 3,
    "Youtube": 4,
    "Coinbase": 5,
    "Coinbase Currencies": 6,
    "Spotify User Search": 7,
    "Love Meter": 8,
    "Google Calendar": 9,
    "Covid Infos": 10,
  }

  /**
   * Launched in loop.
   */
  useEffect(() => {
        if (!mounted)
        {
          setMounted(what => {
            beginCardsList();
            return true;
          });
        }

        setUpdated(updated => {
          if (updated)
          {
            setUpdated(false)
            saveItemsPosition();
          }
          return false;
        })

        return () => {};
    }), [];

  /**
   * Handles the drag & drop system.
   * @param {*} param0 
   */
  const handleDragEnd = ({destination, source}) => {
    if (!destination) {
      return
    }

    if (destination.index === source.index && destination.droppableId === source.droppableId) {
      return
    }

    // Creating a copy of item before removing it from state
    const itemCopy = {...state[source.droppableId].items[source.index]}

    setState(prev => {
      prev = {...prev}
      // Remove from previous items array
      prev[source.droppableId].items.splice(source.index, 1)


      // Adding to new items array location
      prev[destination.droppableId].items.splice(destination.index, 0, itemCopy)

      setUpdated(true)
      return prev
    })
  }

  /**
   * Updates an item.
   * @param {*} string Name.
   * @param {*} iconName Icon Name.
   * @param {*} typed Service or Widget.
   * @param {*} content Content.
   * @param {*} index New Index.
   * @param {*} prev Previous Index.
   */
  const updateItem = (string, iconName, typed, content, index, prev) => {
    var newItem = {
        id: v4(),
        name: string,
        icon: iconName,
        type: typed,
        widgetId: widgetsIds[string],
        widgoeuf: (<div>{content}</div>)
    };

    console.log("update")

    var items = prev.widgets.items;
    items[index] = newItem;
    return {
      widgets: {
        title: "",
        items: [
          ...items
        ]
      }
    };
  }

  /**
   * Deletes an item by name.
   * @param {*} e
   */
  const deleteItem = (e) => {
    var itemName = e;
    setState(prev => {


      var newItems = prev.widgets.items;

      for (let i = 0; i < newItems.length; ++i)
      {
        if (newItems[i].name === itemName)
        {
          newItems.splice(i, 1);
          break;
        }
      }

      setUpdated(true)
      return {
        widgets: {
          title: "",
          items: [
            ...newItems
          ]
        }
      };
    });
  }

  /**
   * Adds an item considering its name, its icon and its content.
   * @param {*} string Name
   * @param {*} iconName Icon Name.
   * @param {*} type Service or Widget.
   * @param {*} content Content.
   */
  const addItem = (string, iconName, typed, content) => {
    var newItem = {
        id: v4(),
        name: string,
        icon: iconName,
        type: typed,
        widgetId: widgetsIds[string],
        widgoeuf: (
        <div>
          {content}
        </div>
        )
    };

    setState(prev => {

    console.log("Adding...");
    var items = prev.widgets.items;

    if (typed === "Service")
    {
      for (let i = 0; i < items.length; ++i)
      {
        if (items[i].name == string)
          return updateItem(string, iconName, typed, content, i, prev);
      }
    }

    return {
        widgets: {
          title: "",
          items: [
            newItem,
            ...prev.widgets.items
          ]
        }
      };
    })
    setUpdated(true)
    return newItem;
  }

  /**
   * @brief Adds a weather widget.
   */
  const addWeather = () => {
    addItem("Weather", "", "Widget", (<Weather />));
  }

  /**
   * @brief Adds a youtube widget.
   */
  const addYoutube = () => {
    addItem("Youtube", "youtube", "Widget", (<Youtube />));
  }

  /**
   * @brief Adds a coinbase widget.
   */
  const addCoinbase = () => {
    addItem("Coinbase", "coinbase", "Service", (<Coinbase/>))
  }

  /**
   * @brief Adds a coinbase currencies widget.
   */
  const addCoinbaseCurrencies = () => {
    addItem("Coinbase Currencies", "coinbaseCurrencies", "Widget", (<CoinbaseCurrencies/>))
  }

  /**
   * @brief Adds a gmail widget.
   */
  const addGmail = () => {
    addItem("Gmail", "gmail", "Service", (<Gmail />))
  }

  /**
   * @brief Adds a spotify widget.
   */
  const addSpotify = () => {
    addItem("Spotify", "spotify", "Service", (<Spotify />))
  }

  /**
  * @brief Adds a spotify widget.
  */
  const addSpotifyUserSearch = () => {
    addItem("Spotify User Search", "spotify", "Widget", (<SpotifyUserSearch />))
  }

  /**
  * @brief Adds a love widget.
  */
  const addLoveCalculator = () => {
    addItem("Love Meter", "love", "Widget", (<LoveCalculator />))
  }

  /**
  * @brief Adds a covid widget.
  */
  const addCovid = () => {
    addItem("Covid Infos", "covid", "Widget", (<Covid />))
  }

  /**
  * @brief Adds a calendar widget.
  */
  const addCalendar = () => {
    addItem("Google Calendar", "calendar", "Service", (<Calendar />))
  }

  /**
   * Loads the previously invoked widgets.
   */
  const beginCardsList = () => {
    const widgetsNamesByIds = new Map()

    console.log("nan mais what")

    widgetsNamesByIds.set("1", addSpotify);
    widgetsNamesByIds.set("2", addGmail);
    widgetsNamesByIds.set("3", addWeather);
    widgetsNamesByIds.set("4", addYoutube);
    widgetsNamesByIds.set("5", addCoinbase);
    widgetsNamesByIds.set("6", addCoinbaseCurrencies);
    widgetsNamesByIds.set("7", addSpotifyUserSearch);
    widgetsNamesByIds.set("8", addLoveCalculator);
    widgetsNamesByIds.set("9", addCalendar);
    widgetsNamesByIds.set("10", addCovid);

    fetch(`/db/retrieve`)
    .then(res => {
      if (!res.ok) {
        throw new Error("Configuration bug");
      }
      return res.text()
    })
    .then(res => {
      console.log(res);
      res.split('-').forEach(widgetId => {
        console.log(widgetId)
        if (widgetsNamesByIds.has(widgetId))
        {
          widgetsNamesByIds.get(widgetId)();
        }
      });
    })
    .catch(error => {
      console.log(error.message)
    })
  };

  /**
   * Saves the used widgets in the actual order they are displayed.
   */
  const saveItemsPosition = () => {
    var itemsString = "";

    setState(res => {
      res.widgets.items.forEach(item => {
        itemsString += "-" + item.widgetId.toString();
      });
      var splitted = itemsString.split("");
      splitted = splitted.reverse();
      itemsString = splitted.join("");
      console.log(itemsString);

      fetch(`/db/insert/${itemsString}`);
      return res;
    });
  };

/**

  *  RENDER

 */


    return (
    <div className="zizi">
      <div className="buttons">
        <div className="titlePart"><center>Widgets</center></div>
        <button onClick={addWeather} className="big-button">
          <span className="icon weather"> <span className="tooltiptext">Weather</span> </span>
        </button>
        <button onClick={addCoinbase} className="big-button">
            <span className="icon coinbase"> <span className="tooltiptext">Coinbase</span> </span>
        </button>
        <button onClick={addGmail} className="big-button">
          <span className="icon gmail"> <span className="tooltiptext">Google Mail</span> </span>
        </button>
        <button onClick={addCoinbaseCurrencies} className="big-button">
            <span className="icon coinbaseCurrencies"> <span className="tooltiptext">Coinbase Currencies</span> </span>
        </button>
        <button onClick={addCalendar} className="big-button">
          <span className="icon calendar"> <span className="tooltiptext">Google Calendar</span> </span>
        </button>
        <button onClick={addSpotify} className="big-button">
          <span className="icon spotify"> <span className="tooltiptext">My Spotify</span> </span>
        </button>
        <button onClick={addYoutube} className="big-button">
          <span className="icon youtube"> <span className="tooltiptext">Youtube</span> </span>
        </button>
        <button onClick={addSpotifyUserSearch} className="big-button">
          <span className="icon spotify"> <span className="tooltiptext">Spotify User Search</span> </span>
        </button>
        <button onClick={addLoveCalculator} className="big-button">
          <span className="icon love"> <span className="tooltiptext">Love Meter</span> </span>
        </button>
        <button onClick={addCovid} className="big-button">
          <span className="icon covid"> <span className="tooltiptext">Covid Informations</span> </span>
        </button>
      </div>
      <div className="widgets">
        <div className="titlePart"><center>My Widgets</center></div>
      <DragDropContext onDragEnd={handleDragEnd}>
        {_.map(state, (data, key) => {
          return(
            <div key={key} className={"column"}>
              <h3>{data.title}</h3>
              <Droppable droppableId={key}>
                {(provided, snapshot) => {
                  return(
                    <div
                      ref={provided.innerRef}
                      {...provided.droppableProps}
                      className={"droppable-col"}
                    >
                      {data.items.map((el, index) => {
                        return(
                          <Draggable key={el.id} index={index} draggableId={el.id}>
                            {(provided, snapshot) => {
                              console.log(snapshot)
                              return(
                                <div id="widgetView"
                                  className={`big-button ${snapshot.isDragging && "dragging"}`}
                                  ref={provided.innerRef}
                                  {...provided.draggableProps}
                                  {...provided.dragHandleProps}
                                >
                                  <div className="closeSpacer">
                                    <IconButton aria-label="delete" id={`${el.id}`} onClick={(e) => {deleteItem(el.name)}}>
                                      <DeleteIcon />
                                    </IconButton>
                                  </div>
                                  <div>{el.name}</div>
                                  <span className={`icon ${el.icon}`}></span>
                                  <br></br>
                                  {el.widgoeuf}
                                  {provided.placeholder}
                                </div>
                              )
                            }}
                          </Draggable>
                        )
                      })}
                      {provided.placeholder}
                    </div>
                  )
                }}
              </Droppable>
            </div>
          )
        })}
        </DragDropContext>
      </div>
    </div>
  );
}

export default CardsList;

if (document.getElementById('cardsList')) {
    ReactDOM.render(<CardsList />, document.getElementById('cardsList'));
}