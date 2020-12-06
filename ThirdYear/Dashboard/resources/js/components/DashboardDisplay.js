import React from 'react';
import ReactDOM from 'react-dom';
import CardsList from './CardsList';
import { createMuiTheme, MuiThemeProvider } from '@material-ui/core/styles';

const theme = createMuiTheme({
  palette: {
    primary: {
      main: '#80deea99',
      contrastText: '#000',
    },
    secondary: {
      main: '#00bcd499',
      contrastText: '#fff',
    },
  },
});

require("./CardsList");

/**
 * DashboardDisplay widget, contains everything and serves as a theme provider, mainly.
 */
function DashboardDisplay() {
    return (
        <MuiThemeProvider theme={theme}>
            <CardsList />
        </MuiThemeProvider>
    );
}

export default DashboardDisplay;

if (document.getElementById('dashboardDisplay')) {
    ReactDOM.render(<DashboardDisplay />, document.getElementById('dashboardDisplay'));
}
