import React, {useState, useEffect} from 'react';
import _ from "lodash";
import "./App.css";
import TextField from '@material-ui/core/TextField';

import TextareaAutosize from '@material-ui/core/TextareaAutosize';

// Mandatory
import ReactDOM from 'react-dom';

/**
 * Youtube widget.
 */
const Youtube = () => {
    const [initialized, setInitialized] = useState(false);
    const [failure, setFailure] = useState(false);
    const [youtubeData, setData] = useState({
      avatar_cover: "",
      channel_link: "",
      title: "",
      description: "",
      country: "",
      subs: "",
      videoCount: "",
      viewCount: ""
    });

    /**
     * Launched in loop.
     */
    useEffect(() => {
        let mounted = true;

        if (!mounted)
          return;

        updateYoutube("TVFilthyFrank");

        return () => mounted = false;
    }, []);

    /**
     * Handles input bar.
     * @param {*} e
     */
    const youtubeKeyPress = (e) => {
      if(e.key === "Enter") {
        updateYoutube(e.target.value);
        e.preventDefault();
      }
   }

    /**
     * Updates Youtube UI.
     * @param {*} channelName
     */
    const updateYoutube = (channelName) => {
      fetch(`/api/youtube/${channelName}`)
        .then(res => {
          if (!res.ok) {
            throw new Error("Channel not found.");
          }
          return res.json();
        })
        .then(res => {
          console.log(res)
          setData(data => {
            return {
                avatar_cover: res.data.avatar_cover.toString(),
                channel_link: res.data.channel_link.toString(),
                title: res.data.title.toString(),
                description: res.data.description.toString(),
                country: res.data.country,
                subs: res.data.subs.toString(),
                videoCount: res.data.videoCount.toString(),
                viewCount: res.data.viewCount.toString()
            };
          });
          setFailure(false);
          setInitialized(true);
        })
        .catch(function(error) {
          console.log(error.message)
          setFailure(true);
          setInitialized(true);
        })
    }

    return (
      <div>
        {initialized ?
        // Initialized
        <div>
          <form noValidate>
            <TextField onKeyPress={youtubeKeyPress} id="outlined" defaultValue={"TVFilthyFrank"} label="Channel" variant="outlined" />
          </form><br></br>
          {!failure ?
            <div>
                <br></br>
                <span className={`large_icon`} style={{background: 'url(' + youtubeData.avatar_cover + ') no-repeat'}}>
                </span>
                <div className="paragraph">
                  <div className="paragraphCentered" href={`${youtubeData.channel_link}`}>
                    {youtubeData.title}<br></br>
                  </div>
                  <br></br>
                  <TextareaAutosize readOnly
                    className="textAreaMinSize"
                    rowsMax={10}
                    aria-label="maximum height"
                    value={
                      `Description : ${youtubeData.description}`}
                  />
                  <br></br><br></br>
                  {youtubeData.country != null ?
                    <div>
                      Country : {youtubeData.country}<br></br><br></br>
                    </div>
                    :
                    <div>
                      Country : Not specified.
                    </div>
                  }
                  Subscribers : {youtubeData.subs}<br></br>
                  Video count : {youtubeData.videoCount}<br></br>
                  Views       : {youtubeData.viewCount}<br></br>
                </div>
            </div>
            :
            <div>
            Can't load channel's data.
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

export default Youtube;

if (document.getElementById('youtube')) {
    ReactDOM.render(<Youtube />, document.getElementById('youtube'));
}