

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','jquery','react','classnames','resolve!i18n','Dropdown','focus-NotesView-Menu-Selector','focus-NotesView-Menu-Toggle','css!focus/NotesView/NotesViewSubheader','focus-NotesView-AutomationTags'],function (require) {
  

  var $ = require('jquery');
  var React = require('react');
  var classnames = require('classnames');
  var i18n = require('resolve!i18n');

  var Dropdown = require('Dropdown');
  var Selector = require('focus-NotesView-Menu-Selector');
  var Toggle = require('focus-NotesView-Menu-Toggle');
  require('css!focus/NotesView/NotesViewSubheader');

  var AUTOMATION_TAGS = require('focus-NotesView-AutomationTags');
  var BASE_NAME = 'focus-NotesView-Subheader';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  /**
   * Shows the number of notes within a user's current selection, allows the user to
   * switch between business or personal notes, and allows the user to sort the notes
   * that will appear in the corresponding NotesList.
   */
  var NotesViewSubheader = React.createClass({
    displayName: 'NotesViewSubheader',

    propTypes: {
      noteViewOptions: React.PropTypes.shape({
        isShowImages: React.PropTypes.bool.isRequired,
        isShowText: React.PropTypes.bool.isRequired,
        sortOptions: React.PropTypes.arrayOf(React.PropTypes.shape({
          isSelected: React.PropTypes.bool.isRequired,
          label: React.PropTypes.string.isRequired,
          value: React.PropTypes.any.isRequired
        })).isRequired
      }),
      notesPresenter: React.PropTypes.shape({
        setSortOrder: React.PropTypes.func.isRequired,
        toggleShowImages: React.PropTypes.func.isRequired,
        toggleShowText: React.PropTypes.func.isRequired
      }).isRequired,
      totalNotes: React.PropTypes.number.isRequired
    },

    onOptionSelected: function onOptionSelected(value) {
      this.props.notesPresenter.setSortOrder(value);
      this.refs.dropdown.hideMenu();
      $('.NotesView-ScrollWindow').animate({ scrollTop: 0 });
    },

    onShowImagesToggled: function onShowImagesToggled() {
      this.props.notesPresenter.toggleShowImages();
    },

    onShowTextToggled: function onShowTextToggled() {
      this.props.notesPresenter.toggleShowText();
    },

    render: function render() {
      var numNotes = this.props.totalNotes === 1 ? i18n.L('Focus.notesView.subheader.notes.singular', [this.props.totalNotes]) : i18n.L('Focus.notesView.subheader.notes.plural', ['' + this.props.totalNotes]);
      var optionsButton = React.createElement(
        'div',
        { className: prefixedClass('OptionsButton') },
        i18n.L('Focus.notesView.subheader.options')
      );
      return React.createElement(
        'div',
        { className: BASE_NAME },
        React.createElement(
          'div',
          {
            className: classnames(prefixedClass('NotesOverview'), AUTOMATION_TAGS.NOTES_COUNT)
          },
          numNotes
        ),
        React.createElement(
          'div',
          { className: classnames(prefixedClass('OptionsContainer'), AUTOMATION_TAGS.NOTES_OPTIONS)
          },
          React.createElement(
            Dropdown,
            {
              buttonContent: optionsButton,
              isMenuPositionFixed: true,
              ref: 'dropdown'
            },
            React.createElement(
              'legend',
              null,
              i18n.L('Focus.notesView.subheader.options.sortBy.label')
            ),
            React.createElement(Selector, {
              onOptionSelected: this.onOptionSelected,
              options: this.props.noteViewOptions.sortOptions
            }),
            React.createElement('div', { className: 'MenuDivider' }),
            React.createElement(
              'legend',
              null,
              i18n.L('Focus.notesView.subheader.options.viewOptions.label')
            ),
            React.createElement(Toggle, {
              label: i18n.L('Focus.notesView.subheader.options.viewOptions.showImages'),
              onToggle: this.onShowImagesToggled,
              value: this.props.noteViewOptions.isShowImages
            }),
            React.createElement(Toggle, {
              label: i18n.L('Focus.notesView.subheader.options.viewOptions.showText'),
              onToggle: this.onShowTextToggled,
              value: this.props.noteViewOptions.isShowText
            })
          )
        )
      );
    }
  });

  return NotesViewSubheader;
});